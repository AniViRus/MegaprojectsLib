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
    mSubsystems.AddUnique(subsystem);
}

void AAVRPMegaprojectsManager::UnregisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem)
{
    if (!subsystem) return;
    mSubsystems.Remove(subsystem);
}

TArray<AAVRPMegaprojectSubsystemBase*> AAVRPMegaprojectsManager::GetMegaprojects()
{
    return TArray<AAVRPMegaprojectSubsystemBase*>(mSubsystems);
}

bool AAVRPMegaprojectsManager::ShouldSave_Implementation() const
{
    return true;
}

void AAVRPMegaprojectsManager::SetTrackedMegaproject(AAVRPMegaprojectSubsystemBase* subsystem)
{
    trackedSubsystem = subsystem;
    OnTrackedMegaprojectChanged.Broadcast(trackedSubsystem);
}
