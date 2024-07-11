


#include "TelSystemCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interface_TelSystem.h"



ATelSystemCharacter::ATelSystemCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));	
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	bIsHoldingItem = false;
	heldItem = nullptr;

}

void ATelSystemCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
}

void ATelSystemCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector forwardDirction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDirction, inputValue.Y);
	AddMovementInput(rightDirection, inputValue.X);
}

void ATelSystemCharacter::Look(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(inputValue.Y);
	AddControllerYawInput(inputValue.X);
}

void ATelSystemCharacter::HoldItem()
{
	if (!bIsHoldingItem)
	{
		FVector start = GetActorLocation();
		FVector end = start;
		float traceRadius = 444.f;

		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this);
		TArray<FHitResult> hitResults;

		bool bHit = GetWorld()->SweepMultiByObjectType(
			hitResults,
			start,
			end,
			FQuat::Identity,
			FCollisionObjectQueryParams(ECC_Destructible),
			FCollisionShape::MakeSphere(traceRadius),
			collisionParams);
		if (bHit)
		{
			for (const FHitResult& hit : hitResults)
			{
				if (hit.GetActor()->GetClass()->ImplementsInterface(UInterface_TelSystem::StaticClass()))
				{
					FoundActor.Add(hit.GetActor());
				}
			}
			AActor* nearestTelObject = FindNearestActor(GetActorLocation(), FoundActor);
			if (nearestTelObject)
			{
				IInterface_TelSystem::Execute_LaunchItem(nearestTelObject, this, true);
				bIsHoldingItem = true;
				heldItem = nearestTelObject;
			}
		}
	}
	else
	{
		if (bIsHoldingItem && heldItem)
		{
			IInterface_TelSystem::Execute_ReleaseItem(heldItem);
			IInterface_TelSystem::Execute_LaunchItem(heldItem, this, false);
			heldItem = nullptr;
			throwSpeed = 0.f;
		}
		bIsHoldingItem = false;
	}
}

AActor* ATelSystemCharacter::FindNearestActor(FVector origin, TArray<AActor*>& actorsToCheck)
{
	AActor* nearestActor = nullptr;
	float closestDistance = TNumericLimits<float>::Max();

	for (AActor* actor : actorsToCheck)
	{
		if (actor)
		{
			float distance = FVector::Dist(origin, actor->GetActorLocation());
			if (distance < closestDistance)
			{
				closestDistance = distance;
				nearestActor = actor;
			}
		}
	}

	return nearestActor;
}

void ATelSystemCharacter::RotateItem()
{
	if (bIsHoldingItem && heldItem)
	{
		throwSpeed += 0.1f;
		IInterface_TelSystem::Execute_RotateLaunch(heldItem);
	}
}

void ATelSystemCharacter::ThrowItem()
{
	if (bIsHoldingItem && heldItem)
	{
		IInterface_TelSystem::Execute_ThrowItem(heldItem,throwTarget,throwSpeed);
		throwSpeed = 0.f;
		heldItem = nullptr;
		bIsHoldingItem = false;
	}
}

void ATelSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATelSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered,this, &ATelSystemCharacter::Movement);
	enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ATelSystemCharacter::Look);
	enhancedInputComponent->BindAction(holdItemAction, ETriggerEvent::Started, this, &ATelSystemCharacter::HoldItem);
	enhancedInputComponent->BindAction(throwItemAction, ETriggerEvent::Triggered, this, &ATelSystemCharacter::RotateItem);
	enhancedInputComponent->BindAction(throwItemAction, ETriggerEvent::Completed, this, &ATelSystemCharacter::ThrowItem);

	enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &ATelSystemCharacter::Jump);
	enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &ATelSystemCharacter::StopJumping);
}

