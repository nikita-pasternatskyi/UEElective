// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEElectiveGameMode.h"
#include "UEElectiveCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEElectiveGameMode::AUEElectiveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
