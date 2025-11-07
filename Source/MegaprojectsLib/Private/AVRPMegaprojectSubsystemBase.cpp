#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPMegaprojectsManager.h"
#include "AVRPUnlockMegaproject.h"
#include "FGSchematicManager.h"
#include "UnrealNetwork.h"

void AAVRPMegaprojectSubsystemBase::BeginPlay()
{
	Super::BeginPlay();
	AAVRPMegaprojectsManager::Get(this)->RegisterMegaprojectSubsystem(this);
	AFGSchematicManager::Get(this)->PurchasedSchematicDelegate.AddDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
	ResolveMegaprojectState();
}

void AAVRPMegaprojectSubsystemBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	AAVRPMegaprojectsManager::Get(this)->UnregisterMegaprojectSubsystem(this);
	AFGSchematicManager::Get(this)->PurchasedSchematicDelegate.RemoveDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
}

int AAVRPMegaprojectSubsystemBase::GetCurrentLevel()
{
	int phasesUnlocked = 0;
	for (auto phase : megaprojectPhases) {
		if (AFGSchematicManager::Get(this)->IsSchematicPurchased(phase)) {
			phasesUnlocked++;
		}
	}
	return phasesUnlocked;
}

void AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic)
{
	for (auto phase : megaprojectPhases) {
		if (phase == schematic) {
			OnMegaprojectPhaseChanged.Broadcast(GetCurrentLevel());
			return;
		}
	}

	for (auto unlock : UFGSchematic::GetUnlocks(schematic)) {
		UAVRPUnlockMegaproject* unlockMegaproject = Cast<UAVRPUnlockMegaproject>(unlock);
		if (unlockMegaproject && IsA(unlockMegaproject->megaproject) && mCurrentInitiationStage < EMegaprojectInitiationStage::MIS_Initiated) {
			mCurrentInitiationStage = EMegaprojectInitiationStage::MIS_Unlocked;
			mCurrentDisplayLocation |= unlockMegaproject->displayStarterLocation;
			ResolveMegaprojectState();
			return;
		}
	}
}