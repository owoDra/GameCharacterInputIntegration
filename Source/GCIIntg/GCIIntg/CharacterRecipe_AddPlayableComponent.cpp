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
	InstancingPolicy = ECharacterRecipeInstancingPolicy::Instanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::LocalOnly;
}


void UCharacterRecipe_AddPlayableComponent::StartSetup_Implementation(const FCharacterRecipePawnInfo& Info)
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
		NewDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UCharacterRecipe_AddPlayableComponent, HandleControllerChange));
		Pawn->ReceiveControllerChangedDelegate.Add(NewDelegate);
	}
}

void UCharacterRecipe_AddPlayableComponent::ApplyInputConfig(APawn* Pawn)
{
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

	FinishSetup();
}

void UCharacterRecipe_AddPlayableComponent::HandleControllerChange(APawn* Pawn, AController* OldController, AController* NewController)
{
	if (Pawn && NewController)
	{
		ApplyInputConfig(Pawn);

		Pawn->ReceiveControllerChangedDelegate.RemoveAll(this);
	}
}
