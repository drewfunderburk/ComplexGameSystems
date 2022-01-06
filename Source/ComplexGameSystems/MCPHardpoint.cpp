// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPHardpoint.h"
#include "MCPHull.h"

// Sets default values for this component's properties
UMCPHardpoint::UMCPHardpoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

FMCPHardpointStat UMCPHardpoint::GetStat(FString name)
{
	for (auto& element : GetStats())
	{
		if (element.Name == name)
			return element;
	}
	UE_LOG(LogTemp, Warning, TEXT("No stat found."));
	return FMCPHardpointStat();
}

void UMCPHardpoint::SetStat(FString name, float value, bool isMultiplicative)
{
	FMCPHardpointStat stat = GetStat(name);
	if (stat.Name != "")
	{
		stat.Value = value;
		stat.IsMultiplicative = isMultiplicative;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No stat found with name: %s"), *name);
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
		stats.Add(FMCPHardpointStat(statType.Name));
	}
}

void UMCPHardpoint::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(UMCPHardpoint, statsAsset))
	{
		UpdateStats();
	}

	Super::PostEditChangeProperty(e);
}
