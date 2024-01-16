// Copyright (C) 2024 owoDra

#include "CharacterRecipe_ApplyInputConfig.h"

#include "GCIIntgLogs.h"

#include "PlayableComponent.h"
#include "InputConfig.h"

#include "CharacterInitStateComponent.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterRecipe_ApplyInputConfig)


UCharacterRecipe_ApplyInputConfig::UCharacterRecipe_ApplyInputConfig()
{
	InstancingPolicy = ECharacterRecipeInstancingPolicy::NonInstanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::LocalOnly;
}

void UCharacterRecipe_ApplyInputConfig::StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const
{
	auto* Pawn{ Info.Pawn.Get() };

	if (auto* PC{ Pawn->FindComponentByClass<UPlayableComponent>() })
	{
		auto* LoadedInputConfig
		{
			InputConfig.IsNull() ? nullptr :
			InputConfig.IsValid() ? InputConfig.Get() : InputConfig.LoadSynchronous()
		};

		UE_LOG(LogGCII, Log, TEXT("++InputConfig (Name: %s)"), *GetNameSafe(LoadedInputConfig));

		PC->SetInputConfig(LoadedInputConfig);
	}
}
