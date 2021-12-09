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

void UMCPHull::SetBaseStats(TArray<FMCPStat> newStats)
{
	baseStats = newStats;
	UpdateStats();
}

FMCPStat UMCPHull::GetStat(FString name)
{
	for (auto& element : GetStats())
	{
		if (element.Name == name)
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
	// Ensure statsAsset is not null
	if (!statsAsset)
		return;

	// Empty baseStats array
	baseStats.Empty();

	// Get stats from statsAsset and add them to baseStats
	for (auto& statType : statsAsset->Stats)
	{
		baseStats.Add(FMCPStat(statType.Name));
	}


	UpdateStats();
}

#if WITH_EDITOR
void UMCPHull::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, statsAsset))
	{
		if (statsAsset)
			UpdateBaseStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, baseStats))
	{
		if (baseStats.Num())
			UpdateStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, hardpoints))
	{
		if (baseStats.Num())
			UpdateStats();
	}

	Super::PostEditChangeProperty(e);
}
#endif