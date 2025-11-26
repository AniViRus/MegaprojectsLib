#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGActorRepresentationInterface.h"
#include "FGActorRepresentationManager.h"
#include "FGActorRepresentation.h"
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
class MEGAPROJECTSLIB_API IAVRPMegaprojectInterface : public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	class AAVRPMegaprojectSubsystemBase;
	// Acts as level-specific BeginPlay(), called remotely
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void BeginFromLevel(int level);
	//A lot of vanilla buildables need to have Super::BeginPlay() to get called for proper reconfiguration
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	void OnLevelChanged(int level);
	//Since Megaprojects don't require descriptor, implement building icon for Manager UI here
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Megaproject")
	UTexture2D* GetMegaprojectIcon();
};