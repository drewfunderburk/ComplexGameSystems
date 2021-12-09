// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPHull.h"

// Sets default values for this component's properties
UMCPHull::UMCPHull()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMCPHull::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMCPHull::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMCPHull::SetStatsAsset(UMCPStats* asset)
{
	statsAsset = asset;
	UpdateBaseStats();
}

void UMCPHull::SetBaseStats(TArray<FMCPStat> stats)
{
	baseStats = stats;
	UpdateStats();
}

FMCPStat UMCPHull::GetStat(FString name)
{
	for (auto& element : GetStats())
	{
		if (element.name == name)
			return element;
	}
	UE_LOG(LogTemp, Warning, TEXT("No stat found."));
	return FMCPStat();
}

void UMCPHull::UpdateStats()
{
	// Reset stats to base
	stats = baseStats;
}

void UMCPHull::UpdateBaseStats()
{
}

