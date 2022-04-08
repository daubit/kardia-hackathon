// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockchainInteraction.h"
#include "example.generated.h"

UCLASS()
class KARDIAHACKATHON_API Aexample : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aexample();
	UFUNCTION()
		void examplecb(UBlockchainLinkRequest* response, bool successfull);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
