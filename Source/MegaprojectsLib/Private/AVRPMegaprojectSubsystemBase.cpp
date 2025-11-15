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

int AAVRPMegaprojectSubsystemBase::GetCurrentPhase()
{
	int phasesUnlocked = 0;
	for (auto phase : megaprojectPhases) {
		if (AFGSchematicManager::Get(this)->IsSchematicPurchased(phase.schematic)) {
			phasesUnlocked++;
		}
	}
	return phasesUnlocked;
}

int AAVRPMegaprojectSubsystemBase::GetCurrentLevel()
{
	return GetCurrentPhase() - 1;
}

void AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic)
{
	for (auto phase : megaprojectPhases) {
		if (phase.schematic == schematic) {
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

#if WITH_EDITOR
EDataValidationResult AAVRPMegaprojectSubsystemBase::IsDataValid(FDataValidationContext& validationContext) const {
	EDataValidationResult ValidationResult = Super::IsDataValid(validationContext);

	auto schematics = TArray<TSubclassOf<UFGSchematic>>();
	for (auto phase : megaprojectPhases) {
		if (!IsValid(phase.schematic) || schematics.Contains(phase.schematic)) {
			validationContext.AddError(FText::FromString(TEXT("Invalid schematic found in Megaproject phases. Should not be null or have duplicates.")));
			ValidationResult = EDataValidationResult::Invalid;
		}
		schematics.Add(phase.schematic);
	}
	return ValidationResult;
}
#endif