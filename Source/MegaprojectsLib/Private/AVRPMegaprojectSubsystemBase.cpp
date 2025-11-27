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
	if (!HasAuthority()) return;
	ResolveMegaprojectState();
}

void AAVRPMegaprojectSubsystemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAVRPMegaprojectSubsystemBase, mCurrentInitiationStage);
	DOREPLIFETIME(AAVRPMegaprojectSubsystemBase, mCurrentDisplayLocation);
	DOREPLIFETIME(AAVRPMegaprojectSubsystemBase, mMegaprojectStarterInstance);
	DOREPLIFETIME(AAVRPMegaprojectSubsystemBase, mMegaprojectInstance);
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

TSubclassOf<UFGSchematic> AAVRPMegaprojectSubsystemBase::GetCurrentSchematic()
{
	if (IsFinished()) return nullptr;
	return megaprojectPhases[GetCurrentPhase()].schematic;
}

bool AAVRPMegaprojectSubsystemBase::IsFinished()
{
	return GetCurrentPhase() >= megaprojectPhases.Num();
}

void AAVRPMegaprojectSubsystemBase::RevealLocation()
{
	if (mCurrentDisplayLocation) return;
	mCurrentDisplayLocation = true;
	if (IsValid(mMegaprojectStarterInstance)) {
		mMegaprojectStarterInstance->SetToRepresent(true);
	}
}

void AAVRPMegaprojectSubsystemBase::HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic)
{
	if (!HasAuthority()) return;
	for (auto phase : megaprojectPhases) {
		if (phase.schematic == schematic) {
			OnMegaprojectPhaseChanged.Broadcast(GetCurrentLevel());
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
			return ValidationResult;
		}
		schematics.Add(phase.schematic);
	}
	return ValidationResult;
}
#endif