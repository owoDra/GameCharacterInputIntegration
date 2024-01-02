// Copyright (C) 2023 owoDra

#include "CharacterModifier_ApplyInputConfig.h"

#include "GCIIntgLogs.h"

#include "PlayableComponent.h"
#include "InputConfig.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_ApplyInputConfig)


UCharacterModifier_ApplyInputConfig::UCharacterModifier_ApplyInputConfig()
{
	bOnlyApplyOnLocal = true;
	bApplyOnClient = false;
	bApplyOnServer = false;
}


bool UCharacterModifier_ApplyInputConfig::OnApply(APawn* Pawn) const
{
	const auto bCanApply{ Super::OnApply(Pawn) };

	if (bCanApply)
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
	}

	return bCanApply;
}
