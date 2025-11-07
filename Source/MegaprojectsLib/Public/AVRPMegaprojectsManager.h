#pragma once

#include "CoreMinimal.h"
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
	// Manager getter
	UFUNCTION(BlueprintPure, Category = "Megaprojects", Meta = (DefaultToSelf = "worldContext"))
	static AAVRPMegaprojectsManager* Get(const UObject* worldContext);
	//Call in base subsystems' BeginPlay (and EndPlay if that ever happens)
	void RegisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	void UnregisterMegaprojectSubsystem(AAVRPMegaprojectSubsystemBase* subsystem);
	// Actor-to-subsystem bridge
	UFUNCTION(BlueprintPure, BlueprintCallable)
	AAVRPMegaprojectSubsystemBase* GetSubsystemOf(AActor* actor) const;
	virtual bool ShouldSave_Implementation() const override;
	UFUNCTION(BlueprintCallable)
	void SetTrackedMegaproject(AAVRPMegaprojectSubsystemBase* subsystem);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTrackedMegaprojectChanged OnTrackedMegaprojectChanged;
protected:
	// List of subsystems
	UPROPERTY(BlueprintReadOnly)
	TArray <AAVRPMegaprojectSubsystemBase*> mSubsystems;
	UPROPERTY(BlueprintReadOnly, SaveGame)
	AAVRPMegaprojectSubsystemBase* trackedSubsystem;
};
