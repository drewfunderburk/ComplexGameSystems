// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "Containers/Array.h"

#include "MCPStats.h"
#include "MCPHardpoint.h"

#include "MCPHull.generated.h"

UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class COMPLEXGAMESYSTEMS_API UMCPHull : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMCPHull();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Getters and Setters
	UMCPStats* GetMCPStatsAsset() const { return statsAsset; }
	void SetStatsAsset(UMCPStats* asset);

	TArray<FMCPHullStat> GetStats() const { return stats; }
	TArray<UMCPHardpoint*> GetChildHardpoints() const { return childHardpoints; }
	TArray<UMCPHardpoint*> GetExtraHardpoints() const { return extraHardpoints; }

	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	TArray<UMCPHardpoint*> GetAllHardpoints() const;


	// Create and add a hardpoint to the childHarpdoints array
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	UPARAM(DisplayName = "Hardpoint") UMCPHardpoint* CreateAndAddChildHardpoint(TSubclassOf<UMCPHardpoint> hardpoint);

	// Remove hardpoint from the childHardpoints array
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	UPARAM(DisplayName = "Removed") bool RemoveChildHardpoint(UMCPHardpoint* hardpoint);

	// Add a hardpoint to the extraHardpoints array
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	void AddExtraHardpoint(UMCPHardpoint* hardpoint);

	// Remove a hardpoint from the extraHardpoints array by index
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	bool RemoveExtraHardpointByIndex(int index);

	// Remove a hardpoint from the extraHardpoints array by pointer
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	int RemoveExtraHardpoint(UMCPHardpoint* hardpoint);

	// Get base stat by name
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	float GetBaseStatValue(FString name) const;

	// Set a base stat's value
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	void SetBaseStatValue(FString name, float value);

	// Get stat by name
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	float GetStatValue(FString name) const;

	// Update functions
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "MCP Hull")
	void UpdateStats();

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "MCP Hull")
	void UpdateChildHardpoints();

protected:
	// Reset baseStats back to what it should be from statsAsset with values of 0
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "MCP Hull")
	void ResetBaseStats();

private:
	// Used to auto update properties in details
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

public:
	// Declare delegate types for events
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHardpointDelegate, UMCPHardpoint*, hardpoint);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatDelegate, FMCPHullStat, hullStat);

	// Broadcast when a hardpoint is added to the Extra Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FHardpointDelegate OnExtraHardpointAdded;

	// Broadcast when a hardpoint is removed from the Extra Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FVoidDelegate OnExtraHardpointRemoved;

	// Broadcast when a hardpoint is added to the Child Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FHardpointDelegate OnChildHardpointAdded;

	// Broadcast when a hardpoint is removed from the Child Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FVoidDelegate OnChildHardpointRemoved;

	// Broadcast when a base stat is set via SetBaseStatValue()
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FStatDelegate OnBaseStatValueSet;

private:
	// MCPStats data asset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MCP Hull", meta=(AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

	// Array of base stats from statsAsset
	UPROPERTY(EditAnywhere, EditFixedSize, Category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> baseStats;

	// Array of stats altered by hardpoints
	UPROPERTY(EditAnywhere, EditFixedSize, Category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> stats;

	// Array of child hardpoints
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, Category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> childHardpoints;

	// Array of any extra hardpoints added
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, Category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> extraHardpoints;
};
