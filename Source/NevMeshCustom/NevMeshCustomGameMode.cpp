// Copyright Epic Games, Inc. All Rights Reserved.

#include "NevMeshCustomGameMode.h"
#include "NevMeshCustomCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANevMeshCustomGameMode::ANevMeshCustomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
