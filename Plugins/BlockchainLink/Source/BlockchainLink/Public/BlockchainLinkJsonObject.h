// Copyright 2014-2019 Vladimir Alyamkin. All Rights Reserved.
// From https://github.com/ufna/VaRest/tree/447410c8d8dadfc906eccd63c0ecf0cc878e9f01 under MIT License

#pragma once

#include "Dom/JsonObject.h"
#include "Templates/UnrealTypeTraits.h"
#include "BlockchainLinkJsonValue.h"
#include "BlockchainLinkJsonObject.generated.h"

class UBlockchainLinkJsonValue;

/**
 * Blueprintable FJsonObject wrapper
 */
UCLASS(BlueprintType, Blueprintable)
class BLOCKCHAINLINK_API UBlockchainLinkJsonObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** Reset all internal data */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void Reset();

	/** Get the root Json object */
	TSharedRef<FJsonObject>& GetRootObject();

	/** Set the root Json object */
	void SetRootObject(const TSharedPtr<FJsonObject>& JsonObject);

	//////////////////////////////////////////////////////////////////////////
	// Serialization
	/** Serialize Json to string (formatted with line breaks) */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		FString EncodeJson() const;

	/** Construct Json object from string */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		bool DecodeJson(const FString& JsonString);

	//////////////////////////////////////////////////////////////////////////
	// FJsonObject API

	/** Gets the type of value as string for a given field */
	UFUNCTION(BlueprintPure, Category = "BlockchainLink|Json")
		FString GetFieldTypeString(const FString& FieldName) const;

	/** Returns a list of field names that exist in the object */
	UFUNCTION(BlueprintPure, Category = "BlockchainLink|Json")
		TArray<FString> GetFieldNames() const;

	/** Checks to see if the FieldName exists in the object */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		bool HasField(const FString& FieldName) const;

	/** Remove field named FieldName */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void RemoveField(const FString& FieldName);

	/** Get the field named FieldName as a JsonValue */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		UBlockchainLinkJsonValue* GetField(const FString& FieldName) const;

	/** Add a field named FieldName with a Value */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetField(const FString& FieldName, UBlockchainLinkJsonValue* JsonValue);

	/** Get the field named FieldName as a Json Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<UBlockchainLinkJsonValue*> GetArrayField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of Json Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetArrayField(const FString& FieldName, const TArray<UBlockchainLinkJsonValue*>& InArray);

	/** Adds all of the fields from one json object to this one */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void MergeJsonObject(UBlockchainLinkJsonObject* InJsonObject, bool Overwrite);

	//////////////////////////////////////////////////////////////////////////
	// FJsonObject API Helpers (easy to use with simple Json objects)

	/** Get the field named FieldName as a number. Ensures that the field is present and is of type Json number.
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		float GetNumberField(const FString& FieldName) const;

	/** Add a field named FieldName with Number as value
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetNumberField(const FString& FieldName, float Number);

	/** Get the field named FieldName as an Integer. Ensures that the field is present and is of type Json number. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		int32 GetIntegerField(const FString& FieldName) const;

	/** Add a field named FieldName with Integer as value. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetIntegerField(const FString& FieldName, int32 Number);

	/** Get the field named FieldName as an Int64. Ensures that the field is present and is of type Json number. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		int64 GetInt64Field(const FString& FieldName) const;

	/** Add a field named FieldName with Int64 as value. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetInt64Field(const FString& FieldName, int64 Number);

	/** Get the field named FieldName as a string. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		FString GetStringField(const FString& FieldName) const;

	/** Add a field named FieldName with value of StringValue */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetStringField(const FString& FieldName, const FString& StringValue);

	/** Get the field named FieldName as a boolean. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		bool GetBoolField(const FString& FieldName) const;

	/** Set a boolean field named FieldName and value of InValue */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetBoolField(const FString& FieldName, bool InValue);

	/** Get the field named FieldName as a Json object. */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		UBlockchainLinkJsonObject* GetObjectField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of JsonObject */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetObjectField(const FString& FieldName, UBlockchainLinkJsonObject* JsonObject);

	/** Set a map of fields with String values */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetMapFields_string(const TMap<FString, FString>& Fields);

	/** Set a map of fields with uint8 values */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetMapFields_uint8(const TMap<FString, uint8>& Fields);

	/** Set a map of fields with int32 values */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetMapFields_int32(const TMap<FString, int32>& Fields);

	/** Set a map of fields with int64 values */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetMapFields_int64(const TMap<FString, int64>& Fields);

	/** Set a map of fields with bool values */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetMapFields_bool(const TMap<FString, bool>& Fields);

private:
	/** Internal implementation for setting map fields. */
	template <typename T>
	void SetMapFields_Impl(const TMap<FString, T>& Fields)
	{
		for (auto& field : Fields)
		{
			// No need to support all int types as they're not supported by BP
			if (TIsSame<T, uint8>::Value || TIsSame<T, int32>::Value || TIsSame<T, int64>::Value || TIsSame<T, float>::Value)
			{
				SetNumberField(field.Key, field.Value);
			}
			else if (TIsSame<T, bool>::Value)
			{
				SetBoolField(field.Key, (bool)field.Value);
			}
		}
	}

	/** Internal implementation to get number arrays of different types */
	template <typename T>
	TArray<T> GetTypeArrayField(const FString& FieldName) const
	{
		TArray<T> NumberArray;
		if (!JsonObj->HasTypedField<EJson::Array>(FieldName) || FieldName.IsEmpty())
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s: No field with name %s of type Array"), *VA_FUNC_LINE, *FieldName);
			return NumberArray;
		}

		const TArray<TSharedPtr<FJsonValue>> JsonArrayValues = JsonObj->GetArrayField(FieldName);
		for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonArrayValues); It; ++It)
		{
			const auto Value = (*It).Get();
			if (Value->Type != EJson::Number)
			{
				UE_LOG(LogTemp, Error, TEXT("Not Number element in array with field name %s"), *FieldName);
			}

			NumberArray.Add((*It)->AsNumber());
		}

		return NumberArray;
	}

	//////////////////////////////////////////////////////////////////////////
	// Array fields helpers (uniform arrays)

public:
	/** Get the field named FieldName as a Number Array. Use it only if you're sure that array is uniform!
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<float> GetNumberArrayField(const FString& FieldName) const;

	/** Get the field named FieldName as a Number Array. Use it only if you're sure that array is uniform! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<int32> GetIntegerArrayField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of Number Array
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetNumberArrayField(const FString& FieldName, const TArray<float>& NumberArray);

	/** Get the field named FieldName as a String Array. Use it only if you're sure that array is uniform! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<FString> GetStringArrayField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of String Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetStringArrayField(const FString& FieldName, const TArray<FString>& StringArray);

	/** Get the field named FieldName as a Bool Array. Use it only if you're sure that array is uniform! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<bool> GetBoolArrayField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of Bool Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetBoolArrayField(const FString& FieldName, const TArray<bool>& BoolArray);

	/** Get the field named FieldName as an Object Array. Use it only if you're sure that array is uniform! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<UBlockchainLinkJsonObject*> GetObjectArrayField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of Ob Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		void SetObjectArrayField(const FString& FieldName, const TArray<UBlockchainLinkJsonObject*>& ObjectArray);

private:
	/** Internal JSON data */
	TSharedRef<FJsonObject> JsonObj;
};
