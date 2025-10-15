#pragma once

#include "CoreMinimal.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "Subsystem/ModSubsystem.h"
#include "AVRPMegaprojectsManager.generated.h"

/**
 * A way to easily access any Megaproejct subsystem by actor
 */
UCLASS()
 class MEGAPROJECTSLIB_API AAVRPMegaprojectsManager : public AModSubsystem
{
	GENERATED_BODY()
public:
	// Manager getter
	UFUNCTION(BlueprintPure, Category = "Megaprojects", Meta = (DefaultToSelf = "worldContext"))
	static AAVRPMegaprojectsManager* Get(const UObject* worldContext);
	//Call in base subsystems' BeginPlay (and EndPlay if that ever happens)
	void RegisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	void UnregisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	// Actor-to-subsystem bridge
	UFUNCTION(BlueprintPure, BlueprintCallable)
	AAVRPMegaprojectSubsystemBase* GetSubsystemOf(AActor* actor) const;
	//Gives access to schematic containing Megaprojects Manager buildable
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnlockBaseSchematic();
protected:
	// List of subsystems
	UPROPERTY()
	TArray <AAVRPMegaprojectSubsystemBase*> mSubsystems;
};
