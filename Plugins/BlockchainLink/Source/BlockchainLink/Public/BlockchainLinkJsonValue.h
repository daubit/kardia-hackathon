// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.
// From https://github.com/ufna/VaRest/tree/447410c8d8dadfc906eccd63c0ecf0cc878e9f01 under MIT License

#pragma once

#include "BlockchainLinkJsonValue.generated.h"

class UBlockchainLinkJsonObject;
class FJsonValue;

/**
 * Represents all the types a Json Value can be.
 */
UENUM(BlueprintType)
enum class EnumJson : uint8
{
	None,
	Null,
	String,
	Number,
	Boolean,
	Array,
	Object,
};

/**
 * Blueprintable FJsonValue wrapper
 */
UCLASS(BlueprintType, Blueprintable)
class BLOCKCHAINLINK_API UBlockchainLinkJsonValue : public UObject
{
	GENERATED_UCLASS_BODY()

		/** Create new Json value from FJsonValue (to be used from BlockchainLinkJsonObject) */
		static UBlockchainLinkJsonValue* ConstructJsonValue(const TSharedPtr<FJsonValue>& InValue);

	/** Get the root Json value */
	TSharedPtr<FJsonValue>& GetRootValue();

	/** Set the root Json value */
	void SetRootValue(TSharedPtr<FJsonValue>& JsonValue);

	//////////////////////////////////////////////////////////////////////////
	// FJsonValue API

	/** Get type of Json value (Enum) */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		EnumJson GetType() const;

	/** Get type of Json value (String) */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		FString GetTypeString() const;

	/** Returns true if this value is a 'null' */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		bool IsNull() const;

	/** Returns this value as a double, throwing an error if this is not an Json Number
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		float AsNumber() const;

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		int32 AsInt32() const;

	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		int64 AsInt64() const;

	/** Returns this value as a number, throwing an error if this is not an Json String */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		FString AsString() const;

	/** Returns this value as a boolean, throwing an error if this is not an Json Bool */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		bool AsBool() const;

	/** Returns this value as an array, throwing an error if this is not an Json Array */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		TArray<UBlockchainLinkJsonValue*> AsArray() const;

	/** Returns this value as an object, throwing an error if this is not an Json Object */
	UFUNCTION(BlueprintCallable, Category = "BlockchainLink|Json")
		UBlockchainLinkJsonObject* AsObject();

	//////////////////////////////////////////////////////////////////////////
	// Data

private:
	/** Internal JSON data */
	TSharedPtr<FJsonValue> JsonVal;

	//////////////////////////////////////////////////////////////////////////
	// Helpers

protected:
	/** Simple error logger */
	void ErrorMessage(const FString& InType) const;
};
