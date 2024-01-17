// Copyright (C) 2024 owoDra

#pragma once

#include "Recipe/CharacterRecipe.h"

#include "CharacterRecipe_AddPlayableComponent.generated.h"

class UPlayableComponent;
class UInputConfig;


/**
 * Modifier class to add health component to Pawn
 */
UCLASS()
class UCharacterRecipe_AddPlayableComponent final : public UCharacterRecipe
{
	GENERATED_BODY()
public:
	UCharacterRecipe_AddPlayableComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AddPlayableComponent")
	TSoftClassPtr<UPlayableComponent> ComponentClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "AddPlayableComponent")
	TSoftObjectPtr<UInputConfig> InputConfig{ nullptr };

protected:
	virtual void StartSetup_Implementation(const FCharacterRecipePawnInfo& Info) override;

	void ApplyInputConfig(APawn* Pawn);

	UFUNCTION()
	void HandleControllerChange(APawn* Pawn, AController* OldController, AController* NewController);

};
