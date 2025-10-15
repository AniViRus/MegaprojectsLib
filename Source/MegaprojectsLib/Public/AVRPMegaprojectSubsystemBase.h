#pragma once

#include "CoreMinimal.h"
#include "FGSchematic.h"
#include "FGInventoryComponent.h"
#include "Subsystem/ModSubsystem.h"
#include "FGFactoryConnectionComponent.h"
#include "FGBuildable.h"
#include "AVRPBuildableMegaprojectStarter.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPMegaprojectSubsystemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMegaprojectPhaseChanged, int, Phase);

//Struct for Megaproject's phase definition, used for UI and current phase definition
USTRUCT(BlueprintType)
struct FAVRPMegaprojectPhase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UFGSchematic> schematic;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<int, FText> description;
};
/**
 * Base class representing a specific megaproject. Has essentials for any megaproject
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class MEGAPROJECTSLIB_API AAVRPMegaprojectSubsystemBase : public AModSubsystem
{
	GENERATED_BODY()
public:
	AAVRPMegaprojectSubsystemBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	// Get current Megaproject phase, used for BeginPlay in case player unlocked all phases with cheats before initiating the project
	UFUNCTION(BlueprintCallable)
	int GetCurrentPhase();

	// Returns text which describes currently unlocked functionality of Megaproject
	UFUNCTION(BlueprintCallable)
	FText GetUnlockedDescription();

	// Check if Megaproject got unlocked by checking an instance of Megaproject Starter
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsUnlocked() { return mMegaprojectStarterInstance != nullptr; }
	// Check if Megaproject has been initiated
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInitiated() { return mMegaprojectInstance != nullptr; }

	//A building to associate Megaproject with
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject", meta = (MustImplement = "AVRPMegaprojectInterface", BlueprintBaseOnly))
	TSubclassOf<AFGBuildable> megaprojectBuild;

	UPROPERTY(BlueprintAssignable)
	FOnMegaprojectPhaseChanged OnMegaprojectPhaseChanged;

	//Megaproject phases
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	TMap<int, FAVRPMegaprojectPhase> megaprojectPhases;

	//Location of the Megaproject's starter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectStarterLocation;
	//Location of the Megaproject building
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectLocation;

	//Items delivered to Megaproject are stored in this virtual inventory
	UPROPERTY()
	UFGInventoryComponent* mMegaprojectInventory;
protected:
	UFUNCTION()
	void HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic);
	UFUNCTION()
	void SpawnMegaprojectStarter(bool displayLocation);
	UFUNCTION()
	void SpawnMegaproject();
	UPROPERTY(SaveGame)
	AAVRPBuildableMegaprojectStarter* mMegaprojectStarterInstance;
	UPROPERTY(SaveGame)
	AFGBuildable* mMegaprojectInstance;
};