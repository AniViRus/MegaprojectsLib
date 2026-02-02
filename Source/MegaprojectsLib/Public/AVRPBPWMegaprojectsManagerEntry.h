#pragma once

#include "CoreMinimal.h"
#include "UI/FGUserWidget.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPBPWMegaprojectsManagerEntry.generated.h"

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
	TArray<UFGUserWidget*> GetPayoffSlots();
protected:
	UPROPERTY(BlueprintReadWrite, meta=(BlueprintBaseOnly))
	AAVRPMegaprojectSubsystemBase* cachedSubsystem;
};
