// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPHull.h"

// Sets default values for this component's properties
UMCPHull::UMCPHull()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UpdateHardpoints();
	UpdateStats();
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
	ResetBaseStats();
}

void UMCPHull::SetBaseStats(TArray<FMCPHullStat> newStats)
{
	baseStats = newStats;
	UpdateStats();
}

FMCPHullStat UMCPHull::GetStat(FString name) const
{
	for (auto& element : GetStats())
	{
		if (element.Name == name)
			return element;
	}
	UE_LOG(LogTemp, Warning, TEXT("No stat found with name: %s"), *name);
	return FMCPHullStat();
}

void UMCPHull::SetStat(FString name, float value)
{
	FMCPHullStat stat = GetStat(name);
	if (stat.Name != "")
		stat.Value = value;
	else
		UE_LOG(LogTemp, Warning, TEXT("No stat found with name: %s"), *name);
}

void UMCPHull::UpdateStats()
{
	// Reset stats to base
	stats.Empty();
	for (FMCPHullStat baseStat : baseStats)
	{
		FMCPHullStat stat = { baseStat.Name, baseStat.Value };
		stats.Add(stat);
	}

	for (auto* hardpoint : hardpoints)
	{
		// Ensure hardpoint is valid
		if (!hardpoint)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hardpoint is null."));
			continue;
		}
		// Ensure hardpoint has the same statsAsset as this hull
		if (hardpoint->GetMCPStatsAsset() != statsAsset)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s stats asset does not match Hull: %s"), *hardpoint->GetMCPStatsAsset()->GetName());
			continue;
		}

		// Apply all stats
		for (int i = 0; i < stats.Num(); i++)
		{
			FMCPHardpointStat stat = hardpoint->GetStats()[i];

			if (stat.IsMultiplicative)
				stats[i].Value *= stat.Value;
			if (!stat.IsMultiplicative)
				stats[i].Value += stat.Value;
		}
	}
}

void UMCPHull::UpdateHardpoints()
{
	// Get all MCPHardpoints in children
	if (AActor* owner = GetOwner())
	{
		TArray<UMCPHardpoint*> childHardpoints;
		owner->GetComponents<UMCPHardpoint>(childHardpoints, true);
		hardpoints = childHardpoints;
	}
}

void UMCPHull::ResetBaseStats()
{
	// Empty baseStats array
	baseStats.Empty();

	// Ensure statsAsset is not null
	if (!statsAsset)
		return;

	// Get stats from statsAsset and add them to baseStats
	for (auto& statType : statsAsset->Stats)
	{
		baseStats.Add(FMCPHullStat(statType.Name));
	}

	UpdateHardpoints();
	UpdateStats();
}

#if WITH_EDITOR
void UMCPHull::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, statsAsset))
	{
		ResetBaseStats();
		UpdateHardpoints();
		UpdateStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, baseStats))
	{
		UpdateHardpoints();
		if (baseStats.Num())
			UpdateStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, hardpoints))
	{
		UpdateHardpoints();
		if (baseStats.Num())
			UpdateStats();
	}

	Super::PostEditChangeProperty(e);
}
#endif