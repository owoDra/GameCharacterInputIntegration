// Copyright (C) 2024 owoDra

#include "CharacterRecipe_AddPlayableComponent.h"

#include "GCIIntgLogs.h"

#include "PlayableComponent.h"
#include "InputConfig.h"

#include "CharacterInitStateComponent.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterRecipe_AddPlayableComponent)


UCharacterRecipe_AddPlayableComponent::UCharacterRecipe_AddPlayableComponent()
{
	InstancingPolicy = ECharacterRecipeInstancingPolicy::NonInstanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::LocalOnly;
}


void UCharacterRecipe_AddPlayableComponent::StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const
{
	auto* Pawn{ Info.Pawn.Get() };

	auto* LoadedComponentClass
	{
		ComponentClass.IsNull() ? nullptr :
		ComponentClass.IsValid() ? ComponentClass.Get() : ComponentClass.LoadSynchronous()
	};

	if (ComponentClass)
	{
		auto* NewPC{ NewObject<UPlayableComponent>(Pawn, LoadedComponentClass) };
		NewPC->RegisterComponent();

		UE_LOG(LogGCII, Log, TEXT("+Component (Name: %s, Class: %s)"), *GetNameSafe(NewPC), *GetNameSafe(LoadedComponentClass));

		auto* LoadedInputConfig
		{
			InputConfig.IsNull() ? nullptr :
			InputConfig.IsValid() ? InputConfig.Get() : InputConfig.LoadSynchronous()
		};

		UE_LOG(LogGCII, Log, TEXT("++InputConfig (Name: %s)"), *GetNameSafe(LoadedInputConfig));

		NewPC->SetInputConfig(LoadedInputConfig);
	}
}
