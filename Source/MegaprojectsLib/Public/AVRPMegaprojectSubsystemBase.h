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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMegaprojectStageResolved);

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
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UFGSchematic> schematic;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	// Get current Megaproject phase. Determined by amount of phase schematics unlocked
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentPhase();
	// Level = Phase - 1
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentLevel();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<UFGSchematic> GetCurrentSchematic();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsFinished();

	// Locks Megaproject if it is unlocked and wasn't initiated yet. Use it for your own gimmicks (i.e. You have 3 options for Megaproject's location (3 Megaprojects), initiating one locks others) - recommended calling outside of subsystems themselves
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintAuthorityOnly)
	bool LockMegaproject();

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated)
	EMegaprojectInitiationStage mCurrentInitiationStage;

	//A building subclass to associate Megaproject with. Introduced just to make sure you have actually made everything required for buildable to be considered a Megaproject
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Megaproject", meta = (MustImplement = "AVRPMegaprojectInterface", BlueprintBaseOnly))
	TSubclassOf<AFGBuildableFactory> megaprojectBuild;
	//Is also called before initializing Megaprojects as an extra sign for Manager building to close UI
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMegaprojectStageResolved OnMegaprojectStageResolved;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMegaprojectPhaseChanged OnMegaprojectPhaseChanged;

	//Megaproject phases, as in the amount of states building can be in. When initiated, schematic at index 0 automatically unlocks, its cost doesn't matter.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Megaproject")
	TArray<FAVRPMegaprojectPhase> megaprojectPhases;

	//Location of the Megaproject's initializer
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectStarterLocation;
	//Location of the Megaproject building
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Megaproject")
	FTransform MegaprojectLocation;
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& validationContext) const override;
#endif
protected:
	UFUNCTION()
	void HandleSchematicPurchased(TSubclassOf<UFGSchematic> schematic);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintAuthorityOnly)
	//Resolves spawn of Initializers and Megaproject Buildable itself, not meant for calling when state doesn't change or after Megaproject is initiated
	void ResolveMegaprojectState();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure)
	UStaticMesh* GetPreviewMesh();
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, Replicated, Category = "Megaproject")
	bool mCurrentDisplayLocation = false;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing="OnRep_MegaprojectStarterInstance", SaveGame)
	AAVRPBuildableMegaprojectStarter* mMegaprojectStarterInstance;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing="OnRep_MegaprojectInstance", SaveGame)
	TScriptInterface<IAVRPMegaprojectInterface> mMegaprojectInstance;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnRep_MegaprojectStarterInstance();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnRep_MegaprojectInstance();
};