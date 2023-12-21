// Copyright (C) 2023 owoDra

#include "CharacterModifier_AddPlayableComponent.h"

#include "GCIIntgLogs.h"

#include "PlayableComponent.h"
#include "InputConfig.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_AddPlayableComponent)


void UCharacterModifier_AddPlayableComponent::OnApply(APawn* Pawn) const
{
	check(Pawn)

	UE_LOG(LogGCII, Log, TEXT("[%s] On Instance Apply(%s)"),
		Pawn->HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetNameSafe(this));

	const auto* World{ Pawn->GetWorld() };
	const auto bIsClient{ World->GetNetMode() != NM_DedicatedServer };
	const auto bLocallyControlled{ Pawn->IsLocallyControlled() };

	UE_LOG(LogGCII, Log, TEXT("Adding components for %s to world %s"), *GetPathNameSafe(Pawn), *World->GetDebugDisplayName());

	if (bIsClient && bLocallyControlled)
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
}
