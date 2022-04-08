#include "BlockchainLink.h"
#include "BlockchainLinkSetting.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"

#define LOCTEXT_NAMESPACE "FBlockchainLinkModule"

void FBlockchainLinkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "BlockchainLink",
			LOCTEXT("RuntimeSettingsName", "BlockchainLink"),
			LOCTEXT("RuntimeSettingsDescription", "Configure BlockchainLink plugin parameters"),
			GetMutableDefault<UBlockchainlinkSetting>()
		);
	}
}

void FBlockchainLinkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (UObjectInitialized())
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "BlockchainLink");
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBlockchainLinkModule, BlockchainLink)