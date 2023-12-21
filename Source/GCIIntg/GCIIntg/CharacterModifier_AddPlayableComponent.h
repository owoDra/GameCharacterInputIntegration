// Copyright (C) 2023 owoDra

#pragma once

#include "CharacterModifier.h"

#include "CharacterModifier_AddPlayableComponent.generated.h"

class UPlayableComponent;
class UInputConfig;


/**
 * Modifier class to add health component to Pawn
 */
UCLASS(meta = (DisplayName = "CM Add Health Component"))
class UCharacterModifier_AddPlayableComponent final : public UCharacterModifier
{
	GENERATED_BODY()
public:
	UCharacterModifier_AddPlayableComponent() {}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AddPlayableComponent")
	TSoftClassPtr<UPlayableComponent> ComponentClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "AddPlayableComponent")
	TSoftObjectPtr<UInputConfig> InputConfig{ nullptr };

protected:
	virtual void OnApply(APawn* Pawn) const override;

};
