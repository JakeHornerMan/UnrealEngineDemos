// Copyright Epic Games, Inc. All Rights Reserved.

#include "Playfab_ExampleGameMode.h"
#include "Playfab_ExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlayfab_ExampleGameMode::APlayfab_ExampleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
