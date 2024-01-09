// Copyright (C) 2024 owoDra

#pragma once

#include "CharacterModifier.h"

#include "CharacterModifier_ApplyInputConfig.generated.h"

class UPlayableComponent;
class UInputConfig;


/**
 * Modifier class to apply InputConfig to Playable component
 */
UCLASS(meta = (DisplayName = "CM Apply Input Config"))
class UCharacterModifier_ApplyInputConfig final : public UCharacterModifier
{
	GENERATED_BODY()
public:
	UCharacterModifier_ApplyInputConfig();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ApplyInputConfig")
	TSoftObjectPtr<UInputConfig> InputConfig{ nullptr };

protected:
	virtual bool OnApply(APawn* Pawn) const override;

};
