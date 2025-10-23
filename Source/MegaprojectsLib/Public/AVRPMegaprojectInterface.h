#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "FGActorRepresentationInterface.h"
#include "AVRPMegaprojectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UAVRPMegaprojectInterface : public UFGActorRepresentationInterface
{
	GENERATED_BODY()
};

/**
 * Intreface to identify Buildable as a megaproject.
 */
class MEGAPROJECTSLIB_API IAVRPMegaprojectInterface: public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	// Acts as BeginPlay(), called remotely. Make sure you bind OnPhaseChanged to subsystem's OnMegaprojectPhaseChanged and call buildable's Super::BeginPlay when implementing
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void BeginFromPhase(int phase);
	//A lot of vanilla buildables need to have Super::BeginPlay() to get called for proper reconfiguration
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void OnPhaseChanged(int phase);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Megaproject")
	TSubclassOf<AAVRPMegaprojectSubsystemBase> GetMegaprojectSubsystem();
};