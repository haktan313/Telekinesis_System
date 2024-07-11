// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tel_System_CplusPlusGameMode.h"
#include "Tel_System_CplusPlusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATel_System_CplusPlusGameMode::ATel_System_CplusPlusGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
