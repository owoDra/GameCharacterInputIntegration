// Copyright (C) 2023 owoDra

#include "CharacterModifier_AddPlayableComponent.h"

#include "GCIIntgLogs.h"

#include "PlayableComponent.h"
#include "InputConfig.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_AddPlayableComponent)


UCharacterModifier_AddPlayableComponent::UCharacterModifier_AddPlayableComponent()
{
	bOnlyApplyOnLocal = true;
	bApplyOnClient = false;
	bApplyOnServer = false;
}


bool UCharacterModifier_AddPlayableComponent::OnApply(APawn* Pawn) const
{
	const auto bCanApply{ Super::OnApply(Pawn) };

	if (bCanApply)
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
	}

	return bCanApply;
}
