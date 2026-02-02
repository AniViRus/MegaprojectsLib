#pragma once

#include "CoreMinimal.h"
#include "AVRPBPWMegaprojectsManagerEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMegaprojectEntryClicked, UAVRPBPWMegaprojectsManagerEntry*, Entry);

/**
 * A class representing entry in Megaprojecets Manager widget
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class MEGAPROJECTSLIB_API UAVRPBPWMegaprojectsManagerEntry : public UFGUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	void SetupEntry(AAVRPMegaprojectSubsystemBase* subsystem);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	void UpdateUnlockedDetails();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	UTexture2D* GetMegaprojectIcon();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	FText GetMegaprojectTitle();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	FText GetStatusText();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	void ResolveTrackButtonVisibility();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	void UpdateInitiatedDetails();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	UTexture2D* GetPreviewImage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	FText GetMegaprojectDescription();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	bool GetUnlockedVisibility();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	bool GetInitiatedVisibility();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	FText GetCurLevelText();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (ForceAsFunction))
	TArray<UWidget*> GetPayoffSlots();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMegaprojectEntryClicked OnMegaprojectEntryClicked;
protected:
	UPROPERTY(BlueprintReadWrite, meta=(BlueprintBaseOnly))
	AAVRPMegaprojectSubsystemBase* cachedSubsystem;
};
