#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGActorRepresentationInterface.h"
#include "AVRPBuildableMegaprojectStarter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitiationRequested);

class AAVRPMegaprojectSubsystemBase;
/**
 * A building which represents as an initializer for Megaproject. Not for inheritance
 */
UCLASS(Abstract)
class MEGAPROJECTSLIB_API AAVRPBuildableMegaprojectStarter : public AFGBuildable, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayLocation(bool display);
	UFUNCTION(BlueprintCallable)
	void InitiateMegaproject();
	UPROPERTY(BlueprintAssignable)
	FOnInitiationRequested OnInitiationRequested;
protected:
	UPROPERTY(BlueprintReadWrite, SaveGame)
	TSubclassOf<AAVRPMegaprojectSubsystemBase> MegaprojectSubsystem;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool Display;

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
