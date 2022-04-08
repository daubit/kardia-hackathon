// Copyright 2014-2019 Vladimir Alyamkin. All Rights Reserved.
// From https://github.com/ufna/VaRest/tree/447410c8d8dadfc906eccd63c0ecf0cc878e9f01 under MIT License

#include "BlockchainLinkJsonObject.h"

#include "BlockchainLinkJsonParser.h"
#include "BlockchainLinkJsonValue.h"

#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

UBlockchainLinkJsonObject::UBlockchainLinkJsonObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, JsonObj(MakeShared<FJsonObject>())
{
}

void UBlockchainLinkJsonObject::Reset()
{
	JsonObj = MakeShared<FJsonObject>();
}

TSharedRef<FJsonObject>& UBlockchainLinkJsonObject::GetRootObject()
{
	return JsonObj;
}

void UBlockchainLinkJsonObject::SetRootObject(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObj = JsonObject.ToSharedRef();
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("%s: Trying to set invalid json object as root one. Reset now."), *VA_FUNC_LINE);
		Reset();
	}
}
FString UBlockchainLinkJsonObject::EncodeJson() const
{
	FString OutputString;
	const auto Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObj, Writer);

	return OutputString;
}

bool UBlockchainLinkJsonObject::DecodeJson(const FString& JsonString)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonString);
	TSharedPtr<FJsonObject> OutJsonObj;
	if (FJsonSerializer::Deserialize(Reader, OutJsonObj))
	{
		JsonObj = OutJsonObj.ToSharedRef();
		return true;
	}
	// If we've failed to deserialize the string, we should clear our internal data
	Reset();

	//UE_LOG(LogTemp, Error, TEXT("Json decoding failed for: %s"), *JsonString);

	return false;
}

//////////////////////////////////////////////////////////////////////////
// FJsonObject API

FString UBlockchainLinkJsonObject::GetFieldTypeString(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Null>(FieldName))
	{
		return TEXT("Null");
	}
	else if (!JsonObj->HasTypedField<EJson::String>(FieldName))
	{
		return TEXT("String");
	}
	else if (!JsonObj->HasTypedField<EJson::Number>(FieldName))
	{
		return TEXT("Number");
	}
	else if (!JsonObj->HasTypedField<EJson::Boolean>(FieldName))
	{
		return TEXT("Boolean");
	}
	else if (!JsonObj->HasTypedField<EJson::Object>(FieldName))
	{
		return TEXT("Object");
	}
	else if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		return TEXT("Array");
	}

	//UE_LOG(LogTemp, Warning, TEXT("Field with name %s type unknown"), *FieldName);
	return "";
}

TArray<FString> UBlockchainLinkJsonObject::GetFieldNames() const
{
	TArray<FString> Result;
	JsonObj->Values.GetKeys(Result);

	return Result;
}

bool UBlockchainLinkJsonObject::HasField(const FString& FieldName) const
{
	if (FieldName.IsEmpty())
	{
		return false;
	}

	return JsonObj->HasField(FieldName);
}

void UBlockchainLinkJsonObject::RemoveField(const FString& FieldName)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->RemoveField(FieldName);
}

UBlockchainLinkJsonValue* UBlockchainLinkJsonObject::GetField(const FString& FieldName) const
{
	if (FieldName.IsEmpty())
	{
		return nullptr;
	}

	TSharedPtr<FJsonValue> NewVal = JsonObj->TryGetField(FieldName);
	if (NewVal.IsValid())
	{
		UBlockchainLinkJsonValue* NewValue = NewObject<UBlockchainLinkJsonValue>();
		NewValue->SetRootValue(NewVal);

		return NewValue;
	}

	return nullptr;
}

void UBlockchainLinkJsonObject::SetField(const FString& FieldName, UBlockchainLinkJsonValue* JsonValue)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetField(FieldName, JsonValue->GetRootValue());
}

//////////////////////////////////////////////////////////////////////////
// FJsonObject API Helpers (easy to use with simple Json objects)

float UBlockchainLinkJsonObject::GetNumberField(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Number>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No field with name %s of type Number"), *FieldName);
		return 0.0f;
	}

	return JsonObj->GetNumberField(FieldName);
}

void UBlockchainLinkJsonObject::SetNumberField(const FString& FieldName, float Number)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetNumberField(FieldName, Number);
}

int32 UBlockchainLinkJsonObject::GetIntegerField(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Number>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No field with name %s of type Number"), *FieldName);
		return 0;
	}

	return JsonObj->GetIntegerField(FieldName);
}

void UBlockchainLinkJsonObject::SetIntegerField(const FString& FieldName, int32 Number)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetNumberField(FieldName, Number);
}

int64 UBlockchainLinkJsonObject::GetInt64Field(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Number>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No field with name %s of type Number"), *FieldName);
		return 0;
	}

	return static_cast<int64>(JsonObj->GetNumberField(FieldName));
}

void UBlockchainLinkJsonObject::SetInt64Field(const FString& FieldName, int64 Number)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetNumberField(FieldName, Number);
}

FString UBlockchainLinkJsonObject::GetStringField(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::String>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No field with name %s of type String"), *FieldName);
		return TEXT("");
	}

	return JsonObj->GetStringField(FieldName);
}

void UBlockchainLinkJsonObject::SetStringField(const FString& FieldName, const FString& StringValue)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetStringField(FieldName, StringValue);
}

bool UBlockchainLinkJsonObject::GetBoolField(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Boolean>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No field with name %s of type Boolean"), *FieldName);
		return false;
	}

	return JsonObj->GetBoolField(FieldName);
}

void UBlockchainLinkJsonObject::SetBoolField(const FString& FieldName, bool InValue)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetBoolField(FieldName, InValue);
}

TArray<UBlockchainLinkJsonValue*> UBlockchainLinkJsonObject::GetArrayField(const FString& FieldName) const
{
	TArray<UBlockchainLinkJsonValue*> OutArray;
	if (FieldName.IsEmpty())
	{
		return OutArray;
	}

	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Array"), *VA_FUNC_LINE, *FieldName);
		return OutArray;
	}

	TArray<TSharedPtr<FJsonValue>> ValArray = JsonObj->GetArrayField(FieldName);
	for (auto Value : ValArray)
	{
		UBlockchainLinkJsonValue* NewValue = NewObject<UBlockchainLinkJsonValue>();
		NewValue->SetRootValue(Value);

		OutArray.Add(NewValue);
	}

	return OutArray;
}

void UBlockchainLinkJsonObject::SetArrayField(const FString& FieldName, const TArray<UBlockchainLinkJsonValue*>& InArray)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	TArray<TSharedPtr<FJsonValue>> ValArray;

	// Process input array and COPY original values
	for (auto InVal : InArray)
	{
		if (InVal == nullptr)
			continue;

		const TSharedPtr<FJsonValue> JsonVal = InVal->GetRootValue();

		switch (InVal->GetType())
		{
		case EnumJson::None:
			break;

		case EnumJson::Null:
			ValArray.Add(MakeShareable(new FJsonValueNull()));
			break;

		case EnumJson::String:
			ValArray.Add(MakeShareable(new FJsonValueString(JsonVal->AsString())));
			break;

		case EnumJson::Number:
			ValArray.Add(MakeShareable(new FJsonValueNumber(JsonVal->AsNumber())));
			break;

		case EnumJson::Boolean:
			ValArray.Add(MakeShareable(new FJsonValueBoolean(JsonVal->AsBool())));
			break;

		case EnumJson::Array:
			ValArray.Add(MakeShareable(new FJsonValueArray(JsonVal->AsArray())));
			break;

		case EnumJson::Object:
			ValArray.Add(MakeShareable(new FJsonValueObject(JsonVal->AsObject())));
			break;

		default:
			break;
		}
	}

	JsonObj->SetArrayField(FieldName, ValArray);
}

void UBlockchainLinkJsonObject::MergeJsonObject(UBlockchainLinkJsonObject* InJsonObject, bool Overwrite)
{
	if (!InJsonObject || !InJsonObject->IsValidLowLevel())
	{
		return;
	}

	TArray<FString> Keys = InJsonObject->GetFieldNames();

	for (auto Key : Keys)
	{
		if (Overwrite == false && HasField(Key))
		{
			continue;
		}

		SetField(Key, InJsonObject->GetField(Key));
	}
}

UBlockchainLinkJsonObject* UBlockchainLinkJsonObject::GetObjectField(const FString& FieldName) const
{
	if (!JsonObj->HasTypedField<EJson::Object>(FieldName))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Object"), *VA_FUNC_LINE, *FieldName);
		return nullptr;
	}

	const TSharedPtr<FJsonObject> JsonObjField = JsonObj->GetObjectField(FieldName);

	UBlockchainLinkJsonObject* OutRestJsonObj = NewObject<UBlockchainLinkJsonObject>();
	OutRestJsonObj->SetRootObject(JsonObjField);

	return OutRestJsonObj;
}

void UBlockchainLinkJsonObject::SetObjectField(const FString& FieldName, UBlockchainLinkJsonObject* JsonObject)
{
	if (FieldName.IsEmpty() || !JsonObject || !JsonObject->IsValidLowLevel())
	{
		return;
	}

	JsonObj->SetObjectField(FieldName, JsonObject->GetRootObject());
}

void UBlockchainLinkJsonObject::SetMapFields_string(const TMap<FString, FString>& Fields)
{
	for (auto& field : Fields)
	{
		SetStringField(field.Key, field.Value);
	}
}

void UBlockchainLinkJsonObject::SetMapFields_uint8(const TMap<FString, uint8>& Fields)
{
	SetMapFields_Impl(Fields);
}

void UBlockchainLinkJsonObject::SetMapFields_int32(const TMap<FString, int32>& Fields)
{
	SetMapFields_Impl(Fields);
}

void UBlockchainLinkJsonObject::SetMapFields_int64(const TMap<FString, int64>& Fields)
{
	SetMapFields_Impl(Fields);
}

void UBlockchainLinkJsonObject::SetMapFields_bool(const TMap<FString, bool>& Fields)
{
	SetMapFields_Impl(Fields);
}

//////////////////////////////////////////////////////////////////////////
// Array fields helpers (uniform arrays)

TArray<float> UBlockchainLinkJsonObject::GetNumberArrayField(const FString& FieldName) const
{
	return GetTypeArrayField<float>(FieldName);
}

TArray<int32> UBlockchainLinkJsonObject::GetIntegerArrayField(const FString& FieldName) const
{
	return GetTypeArrayField<int32>(FieldName);
}

void UBlockchainLinkJsonObject::SetNumberArrayField(const FString& FieldName, const TArray<float>& NumberArray)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	TArray<TSharedPtr<FJsonValue>> EntriesArray;

	for (auto Number : NumberArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueNumber(Number)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<FString> UBlockchainLinkJsonObject::GetStringArrayField(const FString& FieldName) const
{
	TArray<FString> StringArray;
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName) || FieldName.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Array"), *VA_FUNC_LINE, *FieldName);
		return StringArray;
	}

	const TArray<TSharedPtr<FJsonValue>> JsonArrayValues = JsonObj->GetArrayField(FieldName);
	for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonArrayValues); It; ++It)
	{
		const auto Value = (*It).Get();
		if (Value->Type != EJson::String)
		{
			//UE_LOG(LogTemp, Error, TEXT("Not String element in array with field name %s"), *FieldName);
		}

		StringArray.Add((*It)->AsString());
	}

	return StringArray;
}

void UBlockchainLinkJsonObject::SetStringArrayField(const FString& FieldName, const TArray<FString>& StringArray)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	TArray<TSharedPtr<FJsonValue>> EntriesArray;
	for (auto String : StringArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueString(String)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<bool> UBlockchainLinkJsonObject::GetBoolArrayField(const FString& FieldName) const
{
	TArray<bool> BoolArray;
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName) || FieldName.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Array"), *VA_FUNC_LINE, *FieldName);
		return BoolArray;
	}

	const TArray<TSharedPtr<FJsonValue>> JsonArrayValues = JsonObj->GetArrayField(FieldName);
	for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonArrayValues); It; ++It)
	{
		const auto Value = (*It).Get();
		if (Value->Type != EJson::Boolean)
		{
			//UE_LOG(LogTemp, Error, TEXT("Not Boolean element in array with field name %s"), *FieldName);
		}

		BoolArray.Add((*It)->AsBool());
	}

	return BoolArray;
}

void UBlockchainLinkJsonObject::SetBoolArrayField(const FString& FieldName, const TArray<bool>& BoolArray)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	TArray<TSharedPtr<FJsonValue>> EntriesArray;
	for (auto Boolean : BoolArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueBoolean(Boolean)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<UBlockchainLinkJsonObject*> UBlockchainLinkJsonObject::GetObjectArrayField(const FString& FieldName) const
{
	TArray<UBlockchainLinkJsonObject*> OutArray;
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName) || FieldName.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Array"), *VA_FUNC_LINE, *FieldName);
		return OutArray;
	}

	TArray<TSharedPtr<FJsonValue>> ValArray = JsonObj->GetArrayField(FieldName);
	for (const auto& Value : ValArray)
	{
		if (Value->Type != EJson::Object)
		{
			//UE_LOG(LogTemp, Error, TEXT("Not Object element in array with field name %s"), *FieldName);
		}

		TSharedPtr<FJsonObject> NewObj = Value->AsObject();

		UBlockchainLinkJsonObject* NewJson = NewObject<UBlockchainLinkJsonObject>();
		NewJson->SetRootObject(NewObj);

		OutArray.Add(NewJson);
	}

	return OutArray;
}

void UBlockchainLinkJsonObject::SetObjectArrayField(const FString& FieldName, const TArray<UBlockchainLinkJsonObject*>& ObjectArray)
{
	if (FieldName.IsEmpty())
	{
		return;
	}

	TArray<TSharedPtr<FJsonValue>> EntriesArray;
	for (auto Value : ObjectArray)
	{
		if (Value == nullptr)
			continue;

		EntriesArray.Add(MakeShareable(new FJsonValueObject(Value->GetRootObject())));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}