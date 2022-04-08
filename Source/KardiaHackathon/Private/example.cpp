// Fill out your copyright notice in the Description page of Project Settings.

#include "example.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
Aexample::Aexample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aexample::BeginPlay()
{
	Super::BeginPlay();

	UBlockchainInteraction* BlockchainSubsystem = GEngine->GetEngineSubsystem<UBlockchainInteraction>();
	FOnBlockchainRPCRequestCompleteBP cb;
	cb.BindUFunction(this, FName("examplecb"));
	BlockchainSubsystem->getBlockNumber(cb);
}

void Aexample::examplecb(UBlockchainLinkRequest* response, bool successful) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *response->GetResponseContentAsString());
}

// Called every frame
void Aexample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}