#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPUnlockMegaproject.h"
#include "FGSchematicManager.h"
#include "UnrealNetwork.h"

AAVRPMegaprojectSubsystemBase::AAVRPMegaprojectSubsystemBase()
{
	mMegaprojectInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("MegaprojectInventory"));
}

void AAVRPMegaprojectSubsystemBase::BeginPlay()
{
	Super::BeginPlay();
	AFGSchematicManager::Get(this)->PurchasedSchematicDelegate.AddDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
	ResolveMegaprojectState();
}

void AAVRPMegaprojectSubsystemBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	AFGSchematicManager::Get(this)->PurchasedSchematicDelegate.RemoveDynamic(this, &AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased);
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
	for (auto phase : megaprojectPhases) {
		if (phase.Value.schematic == schematic) {
			OnMegaprojectPhaseChanged.Broadcast(GetCurrentPhase());
			return;
		}
	}

	for (auto unlock : UFGSchematic::GetUnlocks(schematic)) {
		UAVRPUnlockMegaproject* unlockMegaproject = Cast<UAVRPUnlockMegaproject>(unlock);
		if (unlockMegaproject && mCurrentInitiationStage < EMegaprojectInitiationStage::MIS_Initiated) {
			mCurrentInitiationStage = EMegaprojectInitiationStage::MIS_Unlocked;
			mCurrentDisplayLocation |= unlockMegaproject->displayStarterLocation;
			ResolveMegaprojectState();
			return;
		}
	}
}