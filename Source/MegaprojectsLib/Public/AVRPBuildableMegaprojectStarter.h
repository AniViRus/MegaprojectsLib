#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPBuildableMegaprojectStarter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitiationRequested);

class AAVRPMegaprojectSubsystemBase;
/**
 * A building which represents as an initializer for Megaproject. Can be derived for extra mechanics
 */
UCLASS(Abstract)
class MEGAPROJECTSLIB_API AAVRPBuildableMegaprojectStarter : public AFGBuildable, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AAVRPBuildableMegaprojectStarter();
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetupStarter(TSubclassOf<AFGBuildable> megaproject, UStaticMesh* mesh, FTransform transform, bool display);
	UFUNCTION(BlueprintCallable)
	void InitiateMegaproject();
	UFUNCTION(BlueprintCallable)
	void SetToRepresent(bool display);
	UFUNCTION(BlueprintCallable)
	void SetToRepresentPref(bool display);
	UFUNCTION(BlueprintCallable)
	void SetDisplayPreviewPref(bool display);
	UPROPERTY(BlueprintAssignable)
	FOnInitiationRequested OnInitiationRequested;
protected:
	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool Display;
	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool DisplayPref = true;
	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool DisplayPreviewPref = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* previewMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMaterialInstance* hologramMaterial;
	UPROPERTY(BlueprintReadOnly, Transient)
	TSubclassOf<AFGBuildable> cachedMegaproject;
private:
	UPROPERTY(Transient)
	UFGActorRepresentation* cachedRepresentation;
	
public:
	//Begin FGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText(const FText& newText) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor(FLinearColor newColor) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance(ECompassViewDistance compassViewDistance) override;
	virtual TArray< FLocalUserNetIdBundle > GetLastEditedBy() const override;
	virtual void SetActorLastEditedBy(const TArray< FLocalUserNetIdBundle >& LastEditedBy) override;
	//End FGActorRepresentationInterface
};
