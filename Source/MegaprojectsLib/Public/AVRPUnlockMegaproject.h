#pragma once

#include "CoreMinimal.h"
#include "Unlocks/FGUnlockInfoOnly.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPUnlockMegaproject.generated.h"

/**
 * Simply an info only unlock which is responsible for enabling ability to initiate the Megaproject.
 * It basically tell the subsystem to spawn a megaproject starter
 * 
 * displayStarterLocation is for gimmick including megaprojects (World Radar won't reveal location at first, but player can find it earlier)
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class MEGAPROJECTSLIB_API UAVRPUnlockMegaproject : public UFGUnlockInfoOnly
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BlueprintBaseOnly))
	TSubclassOf<AAVRPMegaprojectSubsystemBase> megaproject;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool displayStarterLocation = true;
};
