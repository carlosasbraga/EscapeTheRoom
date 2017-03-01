// Copyright Carlos Braga 2017

#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ESCAPETHEROOM_API UMySaveSystem : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Public methods
	// See if the file exists
	UFUNCTION(BlueprintCallable, Category = "Save Game")
	static bool DoesFileExist(const FString Dir, const FString SaveFile, const FString FileExtension = ".sav");
	// Create Save File
	UFUNCTION(BlueprintCallable, Category = "Save Game")
	static bool CreateSaveFile(const FString Dir, const FString SaveFile, const FString FileExtension = ".sav");
	// Save Game State after serialization
	UFUNCTION(BlueprintCallable, Category = "Save Game")
	static bool SaveGameState(USaveGame* SaveGameObject, const FString Dir, const FString SaveFile, const FString FileExtension = ".sav");
	// Load Game State after deserialization
	UFUNCTION(BlueprintCallable, Category = "Save Game")
	static USaveGame* LoadGameState(const FString Dir, const FString SaveFile, const FString FileExtension = ".sav");
};
