#pragma once

#include "CoreMinimal.h"
#include "Unlocks/FGUnlockInfoOnly.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPUnlockMegaproject.generated.h"

/**
 * Simple info only unlock which is responsible for enabling ability to initiate the Megaproject.
 * It basically tells to update Megaproject initiation stage it's related to. 
 * 
 * displayStarterLocation is for gimmick including megaprojects (World Radar's starter won't reveal location at first, but player can find it earlier)
 */
UCLASS( Blueprintable, EditInlineNew, Abstract, DefaultToInstanced )
class MEGAPROJECTSLIB_API UAVRPUnlockMegaproject : public UFGUnlockInfoOnly
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BlueprintBaseOnly))
	TSubclassOf<AAVRPMegaprojectSubsystemBase> megaproject;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool displayStarterLocation = true;
};
