#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlockchainLinkSetting.generated.h"

UCLASS(config = Engine, defaultconfig)
class BLOCKCHAINLINK_API UBlockchainlinkSetting : public UObject
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(config, EditAnywhere, Category = "BlockchainLink Settings")
		FString RPCURL;
};