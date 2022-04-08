#pragma once

#include "CoreMinimal.h"
#include "BlockchainLinkSetting.h"
#include "BlockchainLinkJsonObject.h"
#include "BlockchainLinkJsonValue.h"
#include "BlockchainLinkRequest.h"
#include "Subsystems/EngineSubsystem.h"
#include "BlockchainInteraction.generated.h"

USTRUCT()
struct FBlockchainLinkCallResponse
{
	GENERATED_BODY()

		UPROPERTY()
		FOnBlockchainRPCRequestCompleteBP Callback;

	FDelegateHandle CompleteDelegateHandle;
	FDelegateHandle FailDelegateHandle;

	FBlockchainLinkCallResponse()
	{
	}
};

UCLASS()
class BLOCKCHAINLINK_API UBlockchainInteraction : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UBlockchainInteraction();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Node")
		void nodeInfo(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Node")
		void nodePeers(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Node")
		void nodeDir(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Block")
		void getBlockNumber(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Block")
		void getBlockByHash(const FString& Hash, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Block")
		void getBlockByNumber(int blockNumber, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Block")
		void getBlockHeaderByHash(const FString& Hash, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Block")
		void getBlockHeaderByNumber(int blockNumber, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void kardiaCall(const FString& Data, const FString& From, int gas, int gasPrice, const FString& to, int value, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void estimateGas(const FString& Data, const FString& From, int gas, int gasPrice, const FString& to, int value, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void getLogsFromBlock(int FromBlock, int ToBlock, const FString& Address, TArray<FString> Topics, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void getLogsFromHash(const FString& Address, TArray<FString> Topics, const FString& BlockHash, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void validator(const FString& ValidatorAddress, bool showDelegates, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void validators(bool showDelegates, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void gasPrice(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void getCommit(const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void getValidatorSet(const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Chain")
		void getProof(const FString& Data, TArray<FString> StorageKeys, const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Filter")
		void newFilter(int FromBlock, int ToBlock, const FString& Address, TArray<FString> Topics, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Filter")
		void newBlockFilter(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Filter")
		void uninstallFilter(const FString& FilterId, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Filter")
		void getFilterChanges(const FString& FilterId, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Transactions")
		void sendRawTransaction(const FString& Data, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Transactions")
		void pendingTransactions(const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Transactions")
		void getTransaction(const FString& TxHash, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Transactions")
		void getTransactionReceipt(const FString& TxHash, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Account")
		void getBalance(const FString& Address, const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Account")
		void getNonce(const FString& Address, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Account")
		void getNonceAtHeight(const FString& Address, const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Account")
		void getCode(const FString& Address, const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Methods|Account")
		void getStorageAt(const FString& Address, const FString& pos, const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback);

	/** Construct Json value from string */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		UBlockchainLinkJsonValue* DecodeJsonValue(const FString& JsonString);

	/** Construct Json object from string */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		UBlockchainLinkJsonObject* DecodeJsonObject(const FString& JsonString);

	void OnCallComplete(UBlockchainLinkRequest* Request);

private:
	// used so that we can async get the Callback that should be called for a request
	TMap<UBlockchainLinkRequest*, FBlockchainLinkCallResponse> RequestCallbackMap;

	UBlockchainLinkRequest* ConstructRPCRequest();

	const FString quote(const FString& s);

	bool MakeRequest(const FString& content, const FOnBlockchainRPCRequestCompleteBP& Callback);
};
