

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_TelSystem.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_TelSystem : public UInterface
{
	GENERATED_BODY()
};

class TEL_SYSTEM_CPLUSPLUS_API IInterface_TelSystem
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void RotateLaunch();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void ReleaseItem();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void ThrowItem(AActor* throwTarget, float throwSpeed);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void LaunchItem(AActor* Player, bool canLaunch);

};
