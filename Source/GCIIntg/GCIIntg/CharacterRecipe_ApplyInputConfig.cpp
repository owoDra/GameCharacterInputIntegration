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
	InstancingPolicy = ECharacterRecipeInstancingPolicy::Instanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::LocalOnly;
}


void UCharacterRecipe_ApplyInputConfig::StartSetup_Implementation(const FCharacterRecipePawnInfo& Info)
{
	auto* Pawn{ Info.Pawn.Get() };
	
	// Check for being possessed by a controller.

	if (Pawn->GetController())
	{
		ApplyInputConfig(Pawn);
	}
	else
	{
		FScriptDelegate NewDelegate;
		NewDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UCharacterRecipe_ApplyInputConfig, HandleControllerChange));
		Pawn->ReceiveControllerChangedDelegate.Add(NewDelegate);
	}
}

void UCharacterRecipe_ApplyInputConfig::ApplyInputConfig(APawn* Pawn)
{
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

	FinishSetup();
}

void UCharacterRecipe_ApplyInputConfig::HandleControllerChange(APawn* Pawn, AController* OldController, AController* NewController)
{
	if (Pawn && NewController)
	{
		ApplyInputConfig(Pawn);

		Pawn->ReceiveControllerChangedDelegate.RemoveAll(this);
	}
}
