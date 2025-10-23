#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AVRPTestInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UAVRPTestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * A test class, don't use
 */
class MEGAPROJECTSLIB_API IAVRPTestInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="[dev]avrp_test")
	void AVRPTest();
};
