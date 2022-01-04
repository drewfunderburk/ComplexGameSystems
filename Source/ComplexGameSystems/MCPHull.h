// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "Containers/Array.h"

#include "MCPStats.h"
#include "MCPHardpoint.h"

#include "MCPHull.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	TArray<UMCPHardpoint*> GetHardpoints() const { return hardpoints; }

	// Get base stat by name
	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	float GetBaseStatValue(FString name) const;

	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	void SetBaseStat(FString name, float value);

	// Get stat by name
	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	float GetStatValue(FString name) const;

	// Update functions
	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void UpdateStats();

	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void UpdateHardpoints();
 
protected:
	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void ResetBaseStats();

private:
	// Used to auto update properties in details
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "MCP Hull", meta=(AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> baseStats;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHullStat> stats;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> hardpoints;
};
