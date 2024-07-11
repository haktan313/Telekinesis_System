
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_TelSystem.h"
#include "MainTelObject.generated.h"

UCLASS()
class TEL_SYSTEM_CPLUSPLUS_API AMainTelObject : public AActor, public IInterface_TelSystem
{
	GENERATED_BODY()
	
public:	

	AMainTelObject();

	virtual void Tick(float DeltaTime) override;

	virtual void RotateLaunch_Implementation() override;

	virtual void ReleaseItem_Implementation() override;

	virtual void ThrowItem_Implementation(AActor* throwTarget, float throwSpeed) override;

	virtual void LaunchItem_Implementation(AActor* Player, bool canLaunch) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* mainObject;
	
	AActor* LaunchingPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch")
	AActor* throwTargetFromObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch")
	float maxThrowSpeed;

	bool bCanLaunch;

};
