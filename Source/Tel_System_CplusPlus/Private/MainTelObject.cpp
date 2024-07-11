


#include "MainTelObject.h"


AMainTelObject::AMainTelObject()
{

	PrimaryActorTick.bCanEverTick = true;

	mainObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainObject"));
	RootComponent = mainObject;
	mainObject->SetSimulatePhysics(true);

	bCanLaunch = false;
	
}

void AMainTelObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanLaunch)
	{
		FVector currentAdjustedLocation = LaunchingPlayer->GetActorLocation() + FVector(45.f, 0.f, 65.f);
		FVector rightAdjsutedVectorLocation = LaunchingPlayer->GetActorRightVector() * -150.f;

		FVector bLerpVector = currentAdjustedLocation + rightAdjsutedVectorLocation;
		FVector lerpVector = FMath::Lerp(GetActorLocation(), bLerpVector, 0.08f);
		SetActorLocation(lerpVector);
		mainObject->SetSimulatePhysics(false);
		mainObject->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
}

void AMainTelObject::RotateLaunch_Implementation()
{
	if (bCanLaunch)
	{
		FRotator CurrentRotation = GetActorRotation();
		float Xrotator=CurrentRotation.Roll + 12.f;
		float Yrotator=CurrentRotation.Pitch + 0.f;
		float Zrotator=CurrentRotation.Yaw + 12.f;
		FRotator newRotation = FRotator(Xrotator,Yrotator,Zrotator);
		FRotator lerpRotation = FMath::Lerp(GetActorRotation(), newRotation, 0.4f);
		SetActorRotation(lerpRotation);
	}
}

void AMainTelObject::ReleaseItem_Implementation()
{
	mainObject->SetSimulatePhysics(true);
	mainObject->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AMainTelObject::LaunchItem_Implementation(AActor* Player, bool canLaunch)
{
	LaunchingPlayer = Player;
	bCanLaunch = canLaunch;
}

void AMainTelObject::ThrowItem_Implementation(AActor* throwTarget, float throwSpeed)
{
	if (bCanLaunch)
	{
		float lastThrowSpeed = FMath::Clamp(throwSpeed, 0.f, maxThrowSpeed);
		mainObject->SetSimulatePhysics(true);
		mainObject->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bCanLaunch = false;
		if (throwTarget)
		{
			AActor* newTarget = throwTarget;
			FVector normalizeVector = newTarget->GetActorLocation() - GetActorLocation();
			double a = 0.0001;
			normalizeVector.Normalize(a);
			FVector Impulse = normalizeVector * 222222.f * lastThrowSpeed;
			mainObject->AddImpulseAtLocation(Impulse, GetActorLocation());
		}
		else
		{
			if (LaunchingPlayer)
			{
				if (throwTargetFromObject)
				{
					FVector normalizeVector = throwTargetFromObject->GetActorLocation() - GetActorLocation();
					double a = 0.0001;
					normalizeVector.Normalize(a);
					FVector Impulse3 = normalizeVector * 222222.f * maxThrowSpeed;
					mainObject->AddImpulseAtLocation(Impulse3, GetActorLocation());
				}
				else
				{
					FVector Impulse2 = LaunchingPlayer->GetActorForwardVector() * 222222.f * lastThrowSpeed;
					mainObject->AddImpulseAtLocation(Impulse2, GetActorLocation());
				}
			}
		}
	}
}



