// Copyright (C) 2024 owoDra

#pragma once

#include "Recipe/CharacterRecipe.h"

#include "CharacterRecipe_ApplyInputConfig.generated.h"

class UPlayableComponent;
class UInputConfig;


/**
 * Modifier class to apply InputConfig to Playable component
 */
UCLASS()
class UCharacterRecipe_ApplyInputConfig final : public UCharacterRecipe
{
	GENERATED_BODY()
public:
	UCharacterRecipe_ApplyInputConfig();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ApplyInputConfig")
	TSoftObjectPtr<UInputConfig> InputConfig{ nullptr };

protected:
	virtual void StartSetup_Implementation(const FCharacterRecipePawnInfo& Info) override;

	void ApplyInputConfig(APawn* Pawn);

	UFUNCTION()
	void HandleControllerChange(APawn* Pawn, AController* OldController, AController* NewController);

};
