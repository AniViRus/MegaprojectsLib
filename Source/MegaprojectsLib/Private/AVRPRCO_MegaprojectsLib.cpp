#include "AVRPRCO_MegaprojectsLib.h"
#include "FGSchematicManager.h"
#include "UnrealNetwork.h"

void UAVRPRCO_MegaprojectsLib::InitiateMegaprojectRPC_Implementation(AAVRPBuildableMegaprojectStarter* context)
{
	context->InitiateMegaproject();
}

void UAVRPRCO_MegaprojectsLib::GiveAccessToSchematicRPC_Implementation(TSubclassOf<UFGSchematic> schematic)
{
	AFGSchematicManager::Get(GetWorld())->GiveAccessToSchematic(schematic, nullptr);
}

void UAVRPRCO_MegaprojectsLib::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAVRPRCO_MegaprojectsLib, bDummy);
}
