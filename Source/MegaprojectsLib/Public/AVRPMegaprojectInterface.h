#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGActorRepresentationInterface.h"
#include "AVRPMegaprojectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UAVRPMegaprojectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Intreface to identify Buildable as a megaproject.
 */
class MEGAPROJECTSLIB_API IAVRPMegaprojectInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Megaproject")
	virtual void BeginFromPhase(int phase) = 0;
	UFUNCTION(BlueprintCallable, Category = "Megaproject")
	virtual void OnPhaseChanged(int phase) = 0;
};