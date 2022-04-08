#include "BlockchainInteraction.h"
#include "BlockchainLinkSetting.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "BlockchainLinkJsonObject.h"
#include "BlockchainLinkJsonValue.h"
#include "BlockchainLinkRPCMethods.h"
#include "BlockchainLinkRequest.h"

UBlockchainInteraction::UBlockchainInteraction()
	: UEngineSubsystem()
{
}

void UBlockchainInteraction::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBlockchainInteraction::Deinitialize()
{
	Super::Deinitialize();
}

void UBlockchainInteraction::nodeInfo(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("nodeInfo()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NODE_INFO + "\",\
		\"params\" : [] ,\
		\"id\" : " + RPC_ID +"\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::nodePeers(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("nodePeers()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \""+ NODE_PEERS + "\",\
		\"params\" : [] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::nodeDir(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("nodeDir()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NODE_DATADIR + "\",\
		\"params\" : [] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBlockNumber(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBlockNumber()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + BLOCK_NUMBER + "\",\
		\"params\" : [] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBlockByHash(const FString &Hash, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBlockByHash()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + BLOCK_BY_HASH + "\",\
		\"params\" : [ "+ quote(Hash) +"] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBlockByNumber(int blockNumber, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBlockByNumber()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \""+ BLOCK_BY_NUMBER + "\",\
		\"params\" : [" + FString::FromInt(blockNumber) + "] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBlockHeaderByHash(const FString &Hash, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBlockHeaderByHash()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + BLOCK_HEADER_BY_HASH + "\",\
		\"params\" : [" + quote(Hash) + "] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBlockHeaderByNumber(int blockNumber, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBlockHeaderByNumber()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + BLOCK_HEADER_BY_NUMBER + "\",\
		\"params\" : [" + FString::FromInt(blockNumber) + "] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::kardiaCall(const FString &Data, const FString &From, int Gas, int GasPrice, const FString &To, int Value, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("kardiaCall()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + CALL + "\",\
		\"params\" : [ {\
		\"to\": " + quote(To) + ",\
		\"from\": " + quote(From) + ",\
		\"data\": " + quote(Data) + ",\
		\"gas\": " + FString::FromInt(Gas) + ",\
		\"gasPrice\": " + FString::FromInt(GasPrice) + ",\
		\"value\": " + FString::FromInt(Value) + " }, \"latest\"] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::estimateGas(const FString &Data, const FString &From, int Gas, int GasPrice, const FString &To, int Value, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("estimateGas()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + ESTIMATE_GAS + "\",\
		\"params\" : [ {\
		\"to\": " + quote(To) + ",\
		\"from\": " + quote(From) + ",\
		\"data\": " + quote(Data) + ",\
		\"gas\": " + FString::FromInt(Gas) + ",\
		\"gasPrice\": " + FString::FromInt(GasPrice) + ",\
		\"value\": " + FString::FromInt(Value) + " }, \"latest\"] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::newFilter(int FromBlock, int ToBlock, const FString &Address, TArray<FString> Topics, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("newFilter()"));
	// TODO: Topics can be nested
	FString StringTopics = "[";
	for (const FString topic : Topics) {
		StringTopics += quote(topic);
	}
	StringTopics += "]";
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NEW_FILTER + "\",\
		\"params\" : [ {\
		\"fromBlock\": " + FString::FromInt(FromBlock) + ",\
		\"toBlock\": " + FString::FromInt(ToBlock) + ",\
		\"address\": " + quote(Address) + ",\
		\"topics\": " + StringTopics + " } ] ,\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::newBlockFilter(const FOnBlockchainRPCRequestCompleteBP& Callback) 
{
	UE_LOG(LogTemp, Warning, TEXT("newBlockFilter()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NEW_BLOCK_FILTER + "\",\
		\"params\" : [],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::uninstallFilter(const FString& FilterId, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("uninstallFilter()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + UNINSTALL_FILTER + "\",\
		\"params\" : [" + quote(FilterId) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getFilterChanges(const FString& FilterId, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getFilterChanges()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + FILTER_CHANGES + "\",\
		\"params\" : [" + quote(FilterId) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getLogsFromBlock(int FromBlock, int ToBlock, const FString &Address, TArray<FString> Topics, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getLogs()"));
	// TODO: Topics can be nested
	FString StringTopics = "[";
	for (const FString topic : Topics) {
		StringTopics += quote(topic);
	}
	StringTopics += "]";
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + LOGS + "\",\
		\"params\" : [ {\
		\"fromBlock\": " + FString::FromInt(FromBlock) + ",\
		\"toBlock\": " + FString::FromInt(ToBlock) + ",\
		\"address\": " + quote(Address) + ",\
		\"topics\": " + StringTopics + " } ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getLogsFromHash(const FString &Address, TArray<FString> Topics, const FString &BlockHash, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getLogs()"));
	// TODO: Topics can be nested
	FString StringTopics = "[";
	for (const FString topic : Topics) {
		StringTopics += quote(topic);
	}
	StringTopics += "]";
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + LOGS + "\",\
		\"params\" : [ {\
		\"address\": " + quote(Address) + ",\
		\"blockHash\": " + quote(BlockHash) + ",\
		\"topics\": " + StringTopics + " } ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::validator(const FString& ValidatorAddress, bool showDelegators, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("validator()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + VALIDATOR + "\",\
		\"params\" : [" + quote(ValidatorAddress) + "\
		, " + (showDelegators ? "true" : "false" ) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::validators(bool showDelegators, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("validators()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + VALIDATORS + "\",\
		\"params\" : [" + FString::FString(showDelegators ? "true" : "false") + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::gasPrice(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("gasPrice()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + GAS_PRICE + "\",\
		\"params\" : [],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getCommit(const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getCommit()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + COMMIT + "\",\
		\"params\" : [" + quote(BlockOption) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getValidatorSet(const FString& BlockOption, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getValidatorSet()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + VALIDATOR_SET + "\",\
		\"params\" : [" + quote(BlockOption) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getProof(const FString& Data, TArray<FString> StorageKeys, const FString& BlockOption , const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getProof()"));
	FString StringStorageKeys = "[";
	for (FString storageKeys : StorageKeys) {
		StringStorageKeys += quote(storageKeys);
	}
	StringStorageKeys += "]";
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + PROOF + "\",\
		\"params\" : [ " 
				+ quote(Data) + ","
				+ StringStorageKeys + ","
				+ quote(BlockOption) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::sendRawTransaction(const FString& Data, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("sendRawTransaction()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + SEND_RAW_TX + "\",\
		\"params\" : [ " + quote(Data) + "],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::pendingTransactions(const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("pendingTransactions()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + PENDING_TX + "\",\
		\"params\" : [],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getTransaction(const FString &TxHash, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getTransaction()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + TX + "\",\
		\"params\" : [ " + quote(TxHash) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getTransactionReceipt(const FString &TxHash, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getTransactionReceipt()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + TX_RECEIPT + "\",\
		\"params\" : [ " + quote(TxHash) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getBalance(const FString &Address, const FString& BlockOption , const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getBalance()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + BALANCE + "\",\
		\"params\" : [ " + quote(Address) + ", " + quote(BlockOption) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getNonce(const FString &Address, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getNonce()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NONCE + "\",\
		\"params\" : [ " + quote(Address) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getNonceAtHeight(const FString &Address, const FString &BlockOptions, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getNonceAtHeight()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + NONCE_AT_HEIGHT + "\",\
		\"params\" : [ " + quote(Address) + "," + quote(BlockOptions) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getCode(const FString &Address, const FString &BlockOptions, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getCode()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \""+ CODE + "\",\
		\"params\" : [ " + quote(Address) + "," + quote(BlockOptions) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}

void UBlockchainInteraction::getStorageAt(const FString &Address, const FString &pos, const FString &BlockOptions, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("getStorageAt()"));
	const FString requestContent = "{\
		\"jsonrpc\": \"" + JSON_RPC + "\",\
		\"method\" : \"" + STORAGE_AT + "\",\
		\"params\" : [ " + quote(Address) + "," + quote(pos) + "," + quote(BlockOptions) + " ],\
		\"id\" : " + RPC_ID + "\
    }";
	MakeRequest(requestContent, Callback);
}


UBlockchainLinkRequest* UBlockchainInteraction::ConstructRPCRequest()
{
	return NewObject<UBlockchainLinkRequest>(this);
}

bool UBlockchainInteraction::MakeRequest(const FString& content, const FOnBlockchainRPCRequestCompleteBP& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("MakeRequest"));

	UBlockchainLinkRequest* request = ConstructRPCRequest();

	FBlockchainLinkCallResponse Response;
	Response.Callback = Callback;

	Response.CompleteDelegateHandle = request->OnStaticRequestComplete.AddUObject(this, &UBlockchainInteraction::OnCallComplete);
	Response.FailDelegateHandle = request->OnStaticRequestFail.AddUObject(this, &UBlockchainInteraction::OnCallComplete);
	RequestCallbackMap.Add(request, Response);
	UE_LOG(LogTemp, Warning, TEXT("end"));
	request->ProcessRequest(content);
	return true;
}

UBlockchainLinkJsonValue* UBlockchainInteraction::DecodeJsonValue(const FString& JsonString)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonString);
	TSharedPtr<FJsonValue> OutJsonValue;
	if (FJsonSerializer::Deserialize(Reader, OutJsonValue))
	{
		return UBlockchainLinkJsonValue::ConstructJsonValue(OutJsonValue);
	}

	return nullptr;
}

UBlockchainLinkJsonObject* UBlockchainInteraction::DecodeJsonObject(const FString& JsonString)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonString);
	TSharedPtr<FJsonObject> OutJsonObj;
	if (FJsonSerializer::Deserialize(Reader, OutJsonObj))
	{
		auto NewJsonObj = NewObject<UBlockchainLinkJsonObject>(this);
		NewJsonObj->SetRootObject(OutJsonObj);
		return NewJsonObj;
	}

	return nullptr;
}

void UBlockchainInteraction::OnCallComplete(UBlockchainLinkRequest* Request)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCallComplete"));
	if (!RequestCallbackMap.Contains(Request))
	{
		return;
	}

	const auto Response = RequestCallbackMap.Find(Request);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Request->GetResponseContentAsString());
	Request->OnStaticRequestComplete.Remove(Response->CompleteDelegateHandle);
	Request->OnStaticRequestFail.Remove(Response->FailDelegateHandle);

	Response->Callback.ExecuteIfBound(Request);
	RequestCallbackMap.Remove(Request);
}

const FString UBlockchainInteraction::quote(const FString&s) {
	const FString result = "\"" + s + "\"";
	return result;
}