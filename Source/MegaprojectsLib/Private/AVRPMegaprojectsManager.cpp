#include "AVRPMegaprojectsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Registry/ModContentRegistry.h"
#include "Subsystem/SubsystemActorManager.h"

AAVRPMegaprojectsManager* AAVRPMegaprojectsManager::Get(const UObject* worldContext)
{
    UWorld* WorldObject = GEngine->GetWorldFromContextObjectChecked(worldContext);
    USubsystemActorManager* SubsystemActorManager = WorldObject->GetSubsystem<USubsystemActorManager>();
    check(SubsystemActorManager);
    return SubsystemActorManager->GetSubsystemActor<AAVRPMegaprojectsManager>();
}

void AAVRPMegaprojectsManager::RegisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem)
{
    if (!subsystem) return;
    if (!mSubsystems.Contains(subsystem)) mSubsystems.Add(subsystem);
    for (auto phase : subsystem->megaprojectPhases)
    {
        UModContentRegistry::Get(this)->RegisterSchematic(TEXT("Megaprojects"), phase.Value.schematic);
    }
}

void AAVRPMegaprojectsManager::UnregisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem)
{
    if (!subsystem) return;
    mSubsystems.Remove(subsystem);
}

AAVRPMegaprojectSubsystemBase* AAVRPMegaprojectsManager::GetSubsystemOf(AActor* actor) const
{
    if (!actor) return nullptr;
    for (auto subsystem : mSubsystems) {
        if (actor->IsA(subsystem->megaprojectBuild->StaticClass())) {
        return subsystem;
        }
    }
    return nullptr;
}
