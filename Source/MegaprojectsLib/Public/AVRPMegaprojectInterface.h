#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGActorRepresentationManager.h"
#include "FGActorRepresentationInterface.h"
#include "AVRPMegaprojectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UAVRPMegaprojectInterface : public UFGActorRepresentationInterface
{
	GENERATED_BODY()
};

/**
 * Interface to identify Buildable as a megaproject. Check AVRPBuildableMegaprojectStarter for example of IFGActorRepresentationInterface implementation
 */
class MEGAPROJECTSLIB_API IAVRPMegaprojectInterface: public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	class AAVRPMegaprojectSubsystemBase;
	// Acts as BeginPlay(), called remotely. Make sure you bind OnPhaseChanged to subsystem's OnMegaprojectPhaseChanged and call buildable's Super::BeginPlay when implementing
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void BeginFromPhase(int phase);
	//A lot of vanilla buildables need to have Super::BeginPlay() to get called for proper reconfiguration
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void OnPhaseChanged(int phase);
	//Since Megaprojects don't require descriptor, implement building icon for Manager UI here
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	UTexture2D* GetMegaprojectIcon();
};