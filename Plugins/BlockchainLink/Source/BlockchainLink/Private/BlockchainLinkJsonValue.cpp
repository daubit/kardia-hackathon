// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.
// From https://github.com/ufna/VaRest/tree/447410c8d8dadfc906eccd63c0ecf0cc878e9f01 under MIT License

#include "BlockchainLinkJsonValue.h"
#include "BlockchainLinkJsonObject.h"

UBlockchainLinkJsonValue::UBlockchainLinkJsonValue(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

UBlockchainLinkJsonValue* UBlockchainLinkJsonValue::ConstructJsonValue(const TSharedPtr<FJsonValue>& InValue)
{
	TSharedPtr<FJsonValue> NewVal = InValue;

	UBlockchainLinkJsonValue* NewValue = NewObject<UBlockchainLinkJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

TSharedPtr<FJsonValue>& UBlockchainLinkJsonValue::GetRootValue()
{
	return JsonVal;
}

void UBlockchainLinkJsonValue::SetRootValue(TSharedPtr<FJsonValue>& JsonValue)
{
	JsonVal = JsonValue;
}

//////////////////////////////////////////////////////////////////////////
// FJsonValue API

EnumJson UBlockchainLinkJsonValue::GetType() const
{
	if (!JsonVal.IsValid())
	{
		return EnumJson::None;
	}

	switch (JsonVal->Type)
	{
	case EJson::None:
		return EnumJson::None;

	case EJson::Null:
		return EnumJson::Null;

	case EJson::String:
		return EnumJson::String;

	case EJson::Number:
		return EnumJson::Number;

	case EJson::Boolean:
		return EnumJson::Boolean;

	case EJson::Array:
		return EnumJson::Array;

	case EJson::Object:
		return EnumJson::Object;

	default:
		return EnumJson::None;
	}
}

FString UBlockchainLinkJsonValue::GetTypeString() const
{
	if (!JsonVal.IsValid())
	{
		return "None";
	}

	switch (JsonVal->Type)
	{
	case EJson::None:
		return TEXT("None");

	case EJson::Null:
		return TEXT("Null");

	case EJson::String:
		return TEXT("String");

	case EJson::Number:
		return TEXT("Number");

	case EJson::Boolean:
		return TEXT("Boolean");

	case EJson::Array:
		return TEXT("Array");

	case EJson::Object:
		return TEXT("Object");

	default:
		return TEXT("None");
	}
}

bool UBlockchainLinkJsonValue::IsNull() const
{
	if (!JsonVal.IsValid())
	{
		return true;
	}

	return JsonVal->IsNull();
}

float UBlockchainLinkJsonValue::AsNumber() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Number"));
		return 0.f;
	}

	return static_cast<float>(JsonVal->AsNumber());
}

int32 UBlockchainLinkJsonValue::AsInt32() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Number"));
		return 0.f;
	}

	return static_cast<int32>(JsonVal->AsNumber());
}

int64 UBlockchainLinkJsonValue::AsInt64() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Number"));
		return 0.f;
	}

	return static_cast<int64>(JsonVal->AsNumber());
}

FString UBlockchainLinkJsonValue::AsString() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("String"));
		return FString();
	}

	return JsonVal->AsString();
}

bool UBlockchainLinkJsonValue::AsBool() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Boolean"));
		return false;
	}

	return JsonVal->AsBool();
}

TArray<UBlockchainLinkJsonValue*> UBlockchainLinkJsonValue::AsArray() const
{
	TArray<UBlockchainLinkJsonValue*> OutArray;

	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Array"));
		return OutArray;
	}

	TArray<TSharedPtr<FJsonValue>> ValArray = JsonVal->AsArray();
	for (auto Value : ValArray)
	{
		UBlockchainLinkJsonValue* NewValue = NewObject<UBlockchainLinkJsonValue>();
		NewValue->SetRootValue(Value);

		OutArray.Add(NewValue);
	}

	return OutArray;
}

UBlockchainLinkJsonObject* UBlockchainLinkJsonValue::AsObject()
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Object"));
		return nullptr;
	}

	const TSharedPtr<FJsonObject> NewObj = JsonVal->AsObject();

	UBlockchainLinkJsonObject* JsonObj = NewObject<UBlockchainLinkJsonObject>();
	JsonObj->SetRootObject(NewObj);

	return JsonObj;
}

//////////////////////////////////////////////////////////////////////////
// Helpers

void UBlockchainLinkJsonValue::ErrorMessage(const FString& InType) const
{
	UE_LOG(LogTemp, Error, TEXT("Json Value of type '%s' used as a '%s'."), *GetTypeString(), *InType);
}