#pragma once

#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "AVRPBuildableMegaprojectStarter.h"
#include "AVRPRCO_MegaprojectsLib.generated.h"

/**
 * 
 */
UCLASS()
class MEGAPROJECTSLIB_API UAVRPRCO_MegaprojectsLib : public UFGRemoteCallObject
{
	GENERATED_BODY()
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetDisplayRPC(AAVRPBuildableMegaprojectStarter* context, bool display);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void InitiateMegaprojectRPC(AAVRPBuildableMegaprojectStarter* context);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void GiveAccessToSchematicRPC(TSubclassOf<UFGSchematic> schematic);

	UPROPERTY(Replicated)
	bool bDummy = true;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
