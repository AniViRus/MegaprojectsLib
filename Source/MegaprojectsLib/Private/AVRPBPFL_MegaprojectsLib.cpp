#include "AVRPBPFL_MegaprojectsLib.h"
#include "FGBuildable.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "FGSchematicManager.h"


void UAVRPBPFL_MegaprojectsLib::Factory_PayoffOnMegagproject(AFGBuildable* buildable, AAVRPMegaprojectSubsystemBase* megaproject, TArray<UFGFactoryConnectionComponent*> connections)
{
	if (!buildable->HasAuthority()) return;
	auto schematic = megaproject->GetCurrentSchematic();
	if (!IsValid(schematic)) return;
	auto schematicManager = AFGSchematicManager::Get(buildable);
	for (auto connection : connections) {
		TArray<FInventoryItem> items;
		if (connection->GetDirection() == EFactoryConnectionDirection::FCD_INPUT && connection->IsConnected() && connection->Factory_PeekOutput(items)) {
			while (!items.IsEmpty()) {
				auto remainingCost = schematicManager->GetRemainingCostFor(schematic);
				auto hasItem = false;
				for (auto itemAmount : remainingCost) {
					if (itemAmount.ItemClass == items[0].GetItemClass()) {
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
