

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TelSystemGameMode.generated.h"


UCLASS()
class TEL_SYSTEM_CPLUSPLUS_API ATelSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
