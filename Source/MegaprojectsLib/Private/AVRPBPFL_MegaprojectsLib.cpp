#include "AVRPBPFL_MegaprojectsLib.h"
#include "FGBuildable.h"
#include "AVRPMegaprojectsManager.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "FGSchematicManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


void UAVRPBPFL_MegaprojectsLib::Factory_PayoffOnMegagproject(AFGBuildable* buildable, TArray<UFGFactoryConnectionComponent*> connections)
{
	auto megaproject = GetSubsystemOfByInstance(buildable);
	if (!buildable->HasAuthority() || !IsValid(megaproject) || megaproject->IsFinished()) return;
	auto schematic = megaproject->GetCurrentSchematic();
	auto schematicManager = AFGSchematicManager::Get(buildable);
	for (auto connection : connections) {
		TArray<FInventoryItem> items;
		if (connection->GetDirection() == EFactoryConnectionDirection::FCD_INPUT && connection->IsConnected() && connection->Factory_PeekOutput(items)) {
			while (!items.IsEmpty()) {
				auto remainingCost = schematicManager->GetRemainingCostFor(schematic);
				auto hasItem = false;
				for (auto itemAmount : remainingCost) {
					if (itemAmount.ItemClass == items[0].GetItemClass() && itemAmount.Amount > 0) {
						hasItem = true;
						break;
					}
				}
				if (!hasItem) break;
				auto conveyorItemAmount = TArray<FItemAmount>();
				conveyorItemAmount.Add(FItemAmount(items[0].GetItemClass(), 1));
				schematicManager->PayOffOnSchematic(schematic, conveyorItemAmount);
				float offset;
				FInventoryItem item;
				connection->Factory_GrabOutput(item, offset);
				items.RemoveAt(0);
			}
		}
	}
}

AAVRPMegaprojectSubsystemBase* UAVRPBPFL_MegaprojectsLib::GetSubsystemOfByInstance(AFGBuildable* buildable)
{
	auto schematicManager = AAVRPMegaprojectsManager::Get(buildable);
	if (!IsValid(schematicManager)) return nullptr;
	for (auto megaproject : schematicManager->GetMegaprojects()) {
		if (megaproject->mMegaprojectInstance == buildable) {
			return megaproject;
		}
	}
	return nullptr;
}

AAVRPMegaprojectSubsystemBase* UAVRPBPFL_MegaprojectsLib::GetSubsystemOf(AFGBuildable* buildable)
{
	auto schematicManager = AAVRPMegaprojectsManager::Get(buildable);
	if (!IsValid(schematicManager)) return nullptr;
	for (auto megaproject : schematicManager->GetMegaprojects()) {
		if (UKismetMathLibrary::EqualEqual_ClassClass(megaproject->megaprojectBuild, UGameplayStatics::GetObjectClass(buildable))) {
			return megaproject;
		}
	}
	return nullptr;
}
