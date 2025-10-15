#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPUnlockMegaproject.h"
#include "AVRPMegaprojectsManager.h"
#include "FGSchematicManager.h"

AAVRPMegaprojectSubsystemBase::AAVRPMegaprojectSubsystemBase()
{
	mMegaprojectInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("MegaprojectInventory"));
}

void AAVRPMegaprojectSubsystemBase::BeginPlay()
{
	if (auto manager = AFGSchematicManager::Get(GetWorld()))
	{
		manager->PurchasedSchematicDelegate.AddDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
	}
}

void AAVRPMegaprojectSubsystemBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if(auto manager = AFGSchematicManager::Get(GetWorld()))
	{
		manager->PurchasedSchematicDelegate.RemoveDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
	}
}

int AAVRPMegaprojectSubsystemBase::GetCurrentPhase()
{
	int phasesUnlocked = 0;
	for (auto phase : megaprojectPhases) {
		if (AFGSchematicManager::Get(this)->IsSchematicPurchased(phase.Value.schematic)) {
			phasesUnlocked++;
		}
	}
	return phasesUnlocked;
}

FText AAVRPMegaprojectSubsystemBase::GetUnlockedDescription()
{
	//Implement later
	return FText();
}

void AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic)
{
	auto isSchematicAPhase = false;
	for (auto phase : megaprojectPhases) {
		if (phase.Value.schematic == schematic) {
			OnMegaprojectPhaseChanged.Broadcast(GetCurrentPhase());
			AAVRPMegaprojectsManager::Get(this)->UnlockBaseSchematic();
		}
	}
	for (auto unlock : UFGSchematic::GetUnlocks(schematic)) {
		auto unlockMegaproject = Cast<UAVRPUnlockMegaproject>(unlock);
		if (unlockMegaproject && this->IsA(unlockMegaproject->megaproject)) {
			SpawnMegaprojectStarter(unlockMegaproject->displayStarterLocation);
		}
	}
}

void AAVRPMegaprojectSubsystemBase::SpawnMegaprojectStarter(bool displayLocation)
{
	//Implement later
	//Spawns Megaproject Starter and provides it with relevant data
}

void AAVRPMegaprojectSubsystemBase::SpawnMegaproject()
{
	//Implement later
	//Spawns Megaproject and provides it with relevant data
}
