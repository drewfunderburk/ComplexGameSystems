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
	// Sets default values for this component's properties
	UMCPHull();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UMCPStats* GetMCPStatsAsset() const { return statsAsset; }
	void SetStatsAsset(UMCPStats* asset);

	TArray<FMCPHullStat> GetBaseStats() const { return baseStats; }
	void SetBaseStats(TArray<FMCPHullStat> stats);

	TArray<FMCPHullStat> GetStats() const { return stats; }
	TArray<UMCPHardpoint*> GetHardpoints() const { return hardpoints; }

	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	FMCPHullStat GetStat(FString name);

	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void UpdateStats();

	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void UpdateHardpoints();
 
protected:
	UFUNCTION(CallInEditor, BlueprintCallable, category = "MCP Hull")
	void UpdateBaseStats();

private:
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "MCP Hull", meta=(AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<FMCPHullStat> baseStats;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<FMCPHullStat> stats;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hull", meta = (AllowPrivateAccess = "true"))
	TArray<UMCPHardpoint*> hardpoints;
};
