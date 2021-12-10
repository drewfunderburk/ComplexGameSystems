// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPHardpoint.h"
#include "MCPHull.h"

// Sets default values for this component's properties
UMCPHardpoint::UMCPHardpoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMCPHardpoint::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMCPHardpoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMCPHardpoint::SetMCPStatsAsset(UMCPStats* asset)
{
	statsAsset = asset;
	UpdateStats();
}

void UMCPHardpoint::SetOwningHull(UMCPHull* hull)
{
	if (hull)
		owningHull = hull;
}

void UMCPHardpoint::SetStats(TArray<FMCPStat> newStats)
{
	stats = newStats;
}

FMCPStat UMCPHardpoint::GetStat(FString name)
{
	for (auto& element : GetStats())
	{
		if (element.Name == name)
			return element;
	}
	UE_LOG(LogTemp, Warning, TEXT("No stat found."));
	return FMCPStat();
}

void UMCPHardpoint::UpdateStats()
{
	// Empty baseStats array
	stats.Empty();

	// Ensure statsAsset is not null
	if (!statsAsset)
		return;

	// Get stats from statsAsset and add them to baseStats
	for (auto& statType : statsAsset->Stats)
	{
		stats.Add(FMCPStat(statType.Name));
	}
}

#if WITH_EDITOR
void UMCPHardpoint::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHardpoint, statsAsset))
	{
		UpdateStats();
		if (owningHull)
			owningHull->UpdateStats();
		
	}

	Super::PostEditChangeProperty(e);
}
#endif

