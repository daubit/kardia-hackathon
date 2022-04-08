#include "BlockchainLinkRequest.h"
#include "BlockchainLinkSetting.h"
#include "BlockchainInteraction.h"
#include "BlockchainLinkJsonObject.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

UBlockchainLinkRequest::UBlockchainLinkRequest(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UBlockchainLinkRequest::ResetResponseData()
{
	WasSuccessfull = false;
	ResponseContentJSON = MakeShareable(new FJsonObject);
}

void UBlockchainLinkRequest::ProcessRequest(const FString& content)
{
	UBlockchainlinkSetting* settings = GetMutableDefault<UBlockchainlinkSetting>();
	check(settings);

	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetContentAsString(content);

	HttpRequest->SetURL(settings->RPCURL);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UBlockchainLinkRequest::OnProcessRequestComplete);
	HttpRequest->ProcessRequest();
}

void UBlockchainLinkRequest::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	ResetResponseData();

	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("fail"));
		WasSuccessfull = false;
		OnRequestFail.Broadcast(this);
		OnStaticRequestFail.Broadcast(this);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Response->GetContentAsString());
	TSharedPtr<FJsonObject> OutJsonValue;
	if (FJsonSerializer::Deserialize(Reader, OutJsonValue))
	{
		ResponseContentJSON = OutJsonValue;
	}
	else
	{
		// status 2xx not invalid json
		WasSuccessfull = false;
		OnRequestFail.Broadcast(this);
		OnStaticRequestFail.Broadcast(this);
		return;
	}

	WasSuccessfull = true;
	OnRequestComplete.Broadcast(this);
	OnStaticRequestComplete.Broadcast(this);
}

FString UBlockchainLinkRequest::GetResponseContentAsString()
{
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(ResponseContentJSON.ToSharedRef(), Writer);

	return OutputString;
}

UBlockchainLinkJsonObject* UBlockchainLinkRequest::GetResponseContentAsJSON()
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(GetResponseContentAsString());
	TSharedPtr<FJsonObject> OutJsonObj;
	if (FJsonSerializer::Deserialize(Reader, OutJsonObj))
	{
		auto NewJsonObj = NewObject<UBlockchainLinkJsonObject>(this);
		NewJsonObj->SetRootObject(OutJsonObj);
		return NewJsonObj;
	}

	return nullptr;
}