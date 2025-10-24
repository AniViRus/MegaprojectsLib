#pragma once

#include "CoreMinimal.h"
#include "FGSchematic.h"
#include "FGInventoryComponent.h"
#include "Subsystem/ModSubsystem.h"
#include "FGFactoryConnectionComponent.h"
#include "FGBuildableFactory.h"
#include "FGSaveInterface.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPBuildableMegaprojectStarter.h"
#include "AVRPMegaprojectSubsystemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMegaprojectPhaseChanged, int, Phase);

//Enum to define stage of megaproject initiation
UENUM(BlueprintType)
enum class EMegaprojectInitiationStage : uint8
{
	MIS_None		UMETA(DisplayName = "None"),
	MIS_Unlocked	UMETA(DisplayName = "Unlocked"),
	MIS_Initiated	UMETA(DisplayName = "Initiated")
};

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
class MEGAPROJECTSLIB_API AAVRPMegaprojectSubsystemBase : public AModSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	friend class AAVRPBuildableMegaprojectStarter;
	AAVRPMegaprojectSubsystemBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	// Get current Megaproject phase, used for BeginPlay in case player unlocked all phase schematics with cheats before initiating the project
	UFUNCTION(BlueprintCallable)
	int GetCurrentPhase();

	// Returns text which describes currently unlocked functionality of Megaproject
	UFUNCTION(BlueprintCallable)
	FText GetUnlockedDescription();

	//A building subclass to associate Megaproject with. Introduced just to make sure you have actually made everything required for buildable to be considered a Megaproject
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject", meta = (MustImplement = "AVRPMegaprojectInterface", BlueprintBaseOnly))
	TSubclassOf<AFGBuildableFactory> megaprojectBuild;

	UPROPERTY(BlueprintAssignable)
	FOnMegaprojectPhaseChanged OnMegaprojectPhaseChanged;

	//Megaproject phases, as in the amount of times project can be upgraded after being built
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	TMap<int, FAVRPMegaprojectPhase> megaprojectPhases;

	//Location of the Megaproject's initializer
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectStarterLocation;
	//Location of the Megaproject building
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectLocation;

	//Items delivered to Megaproject are stored in this virtual inventory
	UPROPERTY(SaveGame)
	UFGInventoryComponent* mMegaprojectInventory;
protected:
	// Since I was unable to make Unlock Subsystem work as I need, subsystems handle unlocks on their own
	UFUNCTION()
	void HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResolveMegaprojectState();
	UPROPERTY(BlueprintReadWrite, SaveGame)
	EMegaprojectInitiationStage mCurrentInitiationStage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, Category = "Megaproject")
	bool mCurrentDisplayLocation = false;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	AAVRPBuildableMegaprojectStarter* mMegaprojectStarterInstance;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	TScriptInterface<IAVRPMegaprojectInterface> mMegaprojectInstance;
};