
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TelSystemCharacter.generated.h"

UCLASS()
class TEL_SYSTEM_CPLUSPLUS_API ATelSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* lookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* jumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* holdItemAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* throwItemAction;

public:

	ATelSystemCharacter();

protected:

	virtual void BeginPlay() override;

	void Movement(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void HoldItem();

	void RotateItem();

	void ThrowItem();

	AActor* FindNearestActor(FVector origin, TArray<AActor*>& actorsToCheck);

protected:

	bool bIsHoldingItem;

	AActor* heldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	AActor* throwTarget;

	TArray<AActor*> FoundActor;

	float throwSpeed;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
