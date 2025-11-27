#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AVRPBPFL_MegaprojectsLib.generated.h"

/**
 * 
 */
UCLASS()
class MEGAPROJECTSLIB_API UAVRPBPFL_MegaprojectsLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//I suggest to copy code out of here into your own implementations for performance and reduction of unnecessary checks
	UFUNCTION()
	static void Factory_PayoffOnMegagproject(AFGBuildable* buildable, TArray<UFGFactoryConnectionComponent*> connections);
	UFUNCTION(BlueprintCallable)
	static AAVRPMegaprojectSubsystemBase* GetSubsystemOfByInstance(AFGBuildable* buildable);
};
