// Copyright (C) 2024 owoDra

#pragma once

#include "Modules/ModuleManager.h"

/**
 *  Modules for the main features of the GameCharacter: Input Integration plugin
 */
class FGCIIntgModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
