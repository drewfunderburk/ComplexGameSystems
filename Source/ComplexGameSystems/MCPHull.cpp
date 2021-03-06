// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPHull.h"

// Sets default values for this component's properties
UMCPHull::UMCPHull()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UpdateChildHardpoints();
	UpdateStats();
}

// Called when the game starts
void UMCPHull::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UpdateChildHardpoints();
	UpdateStats(); 
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

TArray<UMCPHardpoint*> UMCPHull::GetAllHardpoints() const
{
	// Return an array containing both childHardpoints and extraHardpoints
	TArray<UMCPHardpoint*> hardpoints;
	hardpoints.Append(childHardpoints);
	hardpoints.Append(extraHardpoints);
	return hardpoints;
}

void UMCPHull::AddExtraHardpoint(UMCPHardpoint* hardpoint)
{
	extraHardpoints.Add(hardpoint);
	UpdateStats();
	OnExtraHardpointAdded.Broadcast(hardpoint);
}

UMCPHardpoint* UMCPHull::CreateAndAddChildHardpoint(TSubclassOf<UMCPHardpoint> hardpoint)
{
	UMCPHardpoint* newHardpoint = NewObject<UMCPHardpoint>(GetOwner(), hardpoint.Get());
	newHardpoint->RegisterComponent();
	GetOwner()->AddOwnedComponent(newHardpoint);
	UpdateChildHardpoints();
	UpdateStats();
	OnChildHardpointAdded.Broadcast(newHardpoint);
	return newHardpoint;
}

bool UMCPHull::RemoveChildHardpoint(UMCPHardpoint* hardpoint)
{
	int item = childHardpoints.Find(hardpoint);
	bool removed = false;
	if (childHardpoints[item])
	{
		childHardpoints[item]->DestroyComponent();
		removed = true;
	}
	
	UpdateChildHardpoints();
	UpdateStats();
	OnChildHardpointRemoved.Broadcast();
	return removed;
}

bool UMCPHull::RemoveExtraHardpointByIndex(int index)
{
	// Ensure valid index
	if (!extraHardpoints.IsValidIndex(index))
		return false;

	extraHardpoints.RemoveAt(index);
	UpdateChildHardpoints();
	UpdateStats();
	OnExtraHardpointRemoved.Broadcast();
	return true;
}

int UMCPHull::RemoveExtraHardpoint(UMCPHardpoint* hardpoint)
{
	int count = extraHardpoints.Remove(hardpoint);
	UpdateChildHardpoints();
	UpdateStats();
	OnExtraHardpointRemoved.Broadcast();
	return count;
}

float UMCPHull::GetBaseStatValue(FString name) const
{
	for (auto& element : baseStats)
	{
		if (element.Name == name)
			return element.Value;
	}
	UE_LOG(LogTemp, Warning, TEXT("No base stat found with name: %s"), *name);
	return -1;
}

void UMCPHull::SetBaseStatValue(FString name, float value)
{
	for (int i = 0; i < baseStats.Num(); i++)
	{
		if (baseStats[i].Name == name)
		{
			baseStats[i].Value = value;
			OnBaseStatValueSet.Broadcast(baseStats[i]);
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("No base stat found with name: %s"), *name);
}

float UMCPHull::GetStatValue(FString name) const
{
	for (auto& element : stats)
	{
		if (element.Name == name)
			return element.Value;
	}
	UE_LOG(LogTemp, Warning, TEXT("No stat found with name: %s"), *name);
	return -1;
}

void UMCPHull::UpdateStats()
{
	// Reset stats to base
	stats.Empty();
	stats = baseStats;

	for (auto* hardpoint : GetAllHardpoints())
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
			if (hardpoint->GetMCPStatsAsset())
				UE_LOG(LogTemp, Warning, TEXT("%s stats asset does not match Hull: %s"), *hardpoint->GetMCPStatsAsset()->GetName());
			continue;
		}

		// Apply all stats
		TArray<FMCPHardpointStat> hardpointStats = hardpoint->GetStats();
		for (int i = 0; i < stats.Num(); i++)
		{
			// CHECKING HERE WHY STATS DON'T STACK
			if (hardpointStats[i].IsMultiplicative)
			{
				stats[i].Value = stats[i].Value * hardpointStats[i].Value;
			}
			if (!hardpointStats[i].IsMultiplicative)
			{
				stats[i].Value = stats[i].Value + hardpointStats[i].Value;
			}
		}
	}
}

void UMCPHull::UpdateChildHardpoints()
{
	// Get all MCPHardpoints in children
	if (AActor* owner = GetOwner())
	{
		TArray<UMCPHardpoint*> hardpoints;
		owner->GetComponents<UMCPHardpoint>(hardpoints, true);
		childHardpoints = hardpoints;
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

	UpdateChildHardpoints();
	UpdateStats();
}

#if WITH_EDITOR
void UMCPHull::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, statsAsset))
	{
		ResetBaseStats();
		UpdateChildHardpoints();
		UpdateStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, baseStats))
	{
		UpdateChildHardpoints();
		if (baseStats.Num())
			UpdateStats();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHull, childHardpoints))
	{
		UpdateChildHardpoints();
		if (baseStats.Num())
			UpdateStats();
	}

	Super::PostEditChangeProperty(e);
}
#endif