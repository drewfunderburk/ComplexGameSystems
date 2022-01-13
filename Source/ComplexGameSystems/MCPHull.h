// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "Containers/Array.h"

#include "MCPStats.h"
#include "MCPHardpoint.h"

#include "MCPHull.generated.h"

//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("")));

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

	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	void AddExtraHardpoint(UMCPHardpoint* hardpoint);

	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	UPARAM(DisplayName = "Hardpoint") UMCPHardpoint* CreateAndAddExtraHardpoint(TSubclassOf<UMCPHardpoint> hardpoint);

	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	bool RemoveExtraHardpointByIndex(int index);

	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	int RemoveExtraHardpoint(UMCPHardpoint* hardpoint);

	// Get base stat by name
	UFUNCTION(BlueprintCallable, Category = "MCP Hull")
	float GetBaseStatValue(FString name) const;

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
 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHardpointDelegate, UMCPHardpoint*, hardpoint);
	// Called when a hardpoint is added to the Extra Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FHardpointDelegate OnExtraHardpointAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);
	// Called when a hardpoint is removed from the Extra Hardpoints List
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FVoidDelegate OnExtraHardpointRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatDelegate, FMCPHullStat, hullStat);
	// Called when a base stat is set via SetBaseStatValue()
	UPROPERTY(BlueprintAssignable, Category = "MCP Hull/Event Dispatchers")
	FStatDelegate OnBaseStatValueSet;

protected:
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "MCP Hull")
	void ResetBaseStats();

private:
	// Used to auto update properties in details
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MCP Hull", meta=(AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

	UPROPERTY(EditAnywhere, EditFixedSize, Category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> baseStats;

	UPROPERTY(EditAnywhere, EditFixedSize, Category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> stats;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, Category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> childHardpoints;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, Category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> extraHardpoints;
};
