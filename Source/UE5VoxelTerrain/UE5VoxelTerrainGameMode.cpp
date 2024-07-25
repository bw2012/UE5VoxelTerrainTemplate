// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5VoxelTerrainGameMode.h"
#include "UE5VoxelTerrainCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5VoxelTerrainGameMode::AUE5VoxelTerrainGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
