#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "BlockchainLinkJsonObject.h"

#include "Runtime/Launch/Resources/Version.h"
#include "BlockchainLinkRequest.generated.h"

// UBlockchainLinkRequest -> Request -> void ?
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlockchainRPCRequestComplete, class UBlockchainLinkRequest*, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlockchainRPCRequestFail, class UBlockchainLinkRequest*, Response);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaticBlockchainRPCRequestComplete, class UBlockchainLinkRequest*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaticBlockchainRPCRequestFail, class UBlockchainLinkRequest*);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBlockchainRPCRequestCompleteBP, UBlockchainLinkRequest*, Response);

UCLASS(BlueprintType, Blueprintable)
class BLOCKCHAINLINK_API UBlockchainLinkRequest : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Request")
		void ProcessRequest(const FString& content);

	UPROPERTY(BlueprintAssignable, Category = "BlockchainLink|Request")
		FOnBlockchainRPCRequestComplete OnRequestComplete;

	UPROPERTY(BlueprintAssignable, Category = "BlockchainLink|Request")
		FOnBlockchainRPCRequestFail OnRequestFail;

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Request")
		FString GetResponseContentAsString();

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Request")
		UBlockchainLinkJsonObject* GetResponseContentAsJSON();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlockchainLink|Request")
		bool WasSuccessfull;
	
	FOnStaticBlockchainRPCRequestComplete OnStaticRequestComplete;

	FOnStaticBlockchainRPCRequestFail OnStaticRequestFail;



private:
	void ResetResponseData();

	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Httprequest went from NotThreadSafe to ThreadSafe in 4.27
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27
	TSharedRef<IHttpRequest, ESPMode::NotThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
#endif

	TSharedPtr<FJsonObject, ESPMode::NotThreadSafe> ResponseContentJSON;

public:
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27
	TSharedRef<IHttpRequest, ESPMode::NotThreadSafe> GetHttpRequest() const { return HttpRequest; };
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetHttpRequest() const { return HttpRequest; };
#endif
};
