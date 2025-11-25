#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGSaveInterface.h"
#include "Subsystem/ModSubsystem.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPMegaprojectsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrackedMegaprojectChanged, AAVRPMegaprojectSubsystemBase*, Megaproject);

/**
 * A way to easily access any Megaproejct subsystem by actor
 */
UCLASS(NotBlueprintable, BlueprintType)
class MEGAPROJECTSLIB_API AAVRPMegaprojectsManager : public AModSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AAVRPMegaprojectsManager();
	// Manager getter
	UFUNCTION(BlueprintPure, Category = "Megaprojects", Meta = (DefaultToSelf = "worldContext", DisplayName = "Get Megaprojects Manager"))
	static AAVRPMegaprojectsManager* Get(const UObject* worldContext);
	//Call in base subsystems' BeginPlay (and EndPlay if that ever happens)
	void RegisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	void UnregisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	UFUNCTION(BlueprintCallable)
	TArray<AAVRPMegaprojectSubsystemBase*> GetMegaprojects();
	virtual bool ShouldSave_Implementation() const override;
	UFUNCTION(BlueprintCallable)
	void SetTrackedMegaproject(AAVRPMegaprojectSubsystemBase* subsystem);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTrackedMegaprojectChanged OnTrackedMegaprojectChanged;
	UPROPERTY(BlueprintReadOnly, SaveGame)
	AAVRPMegaprojectSubsystemBase* trackedSubsystem;
protected:
	// List of subsystems
	UPROPERTY()
	TArray <AAVRPMegaprojectSubsystemBase*> mSubsystems = TArray<AAVRPMegaprojectSubsystemBase*>();
};
