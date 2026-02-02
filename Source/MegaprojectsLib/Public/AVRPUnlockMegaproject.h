#pragma once

#include "CoreMinimal.h"
#include "Unlocks/FGUnlockInfoOnly.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPUnlockMegaproject.generated.h"

/**
 * Simple unlock which is responsible for enabling ability to initiate the Megaproject by setting its state to Unlocked.
 * 
 * displayStarterLocation is for gimmick including megaprojects (World Radar's Initializer won't reveal location at first, but player can find it earlier)
 */
UCLASS( Blueprintable, EditInlineNew, Abstract, DefaultToInstanced )
class MEGAPROJECTSLIB_API UAVRPUnlockMegaproject : public UFGUnlockInfoOnly
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BlueprintBaseOnly))
	TSubclassOf<AAVRPMegaprojectSubsystemBase> megaproject;
};
