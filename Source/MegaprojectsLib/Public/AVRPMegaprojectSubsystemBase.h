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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMegaprojectPhaseChanged, int, NewLevel);

//Enum to define stage of megaproject initiation
UENUM(BlueprintType)
enum class EMegaprojectInitiationStage : uint8
{
	MIS_None		UMETA(DisplayName = "None"),
	MIS_Unlocked	UMETA(DisplayName = "Unlocked"),
	MIS_Initiated	UMETA(DisplayName = "Initiated")
};

//Struct for Megaproject's phase definition, used for UI
USTRUCT(BlueprintType)
struct FAVRPMegaprojectPhase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (MultiLine = true))
	FText description;
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
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	// Get current Megaproject level, starting from 0. Determined by amount of phase schematics unlocked
	UFUNCTION(BlueprintCallable)
	int GetCurrentLevel();

	// Locks Megaproject if it is unlocked and wasn't initiated yet. Use it for your own gimmicks (i.e. You have 3 options for Megaproject's location (3 Megaprojects), initiating one locks others)
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool LockMegaproject();

	UPROPERTY(BlueprintReadWrite, SaveGame)
	EMegaprojectInitiationStage mCurrentInitiationStage;

	//A building subclass to associate Megaproject with. Introduced just to make sure you have actually made everything required for buildable to be considered a Megaproject
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject", meta = (MustImplement = "AVRPMegaprojectInterface", BlueprintBaseOnly))
	TSubclassOf<AFGBuildableFactory> megaprojectBuild;
	//Is also called before initializing Megaprojects as an extra sign for Manager building to close UI
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMegaprojectPhaseChanged OnMegaprojectPhaseChanged;

	//Megaproject levels, as in the amount of states building can be in
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	TArray<FAVRPMegaprojectPhase> megaprojectLevels;
	//Megaproject phases, the amount of times building can be upgraded. By default the count should be equal to "megaprojectLevels - 1"
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	TArray<TSubclassOf<UFGSchematic>> megaprojectPhases;

	//Location of the Megaproject's initializer
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectStarterLocation;
	//Location of the Megaproject building
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectLocation;
protected:
	// Since I was unable to make Unlock Subsystem work as I need, subsystems handle unlocks on their own
	UFUNCTION()
	void HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResolveMegaprojectState();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UStaticMesh* GetPreviewMesh();
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, Category = "Megaproject")
	bool mCurrentDisplayLocation = false;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	AAVRPBuildableMegaprojectStarter* mMegaprojectStarterInstance;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	TScriptInterface<IAVRPMegaprojectInterface> mMegaprojectInstance;
};