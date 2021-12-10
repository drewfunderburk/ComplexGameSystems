// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "MCPStats.h"

#include "MCPHardpoint.generated.h"


class UMCPHull;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMPLEXGAMESYSTEMS_API UMCPHardpoint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMCPHardpoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UMCPStats* GetMCPStatsAsset() const { return statsAsset; }
	void SetMCPStatsAsset(UMCPStats* asset);

	UMCPHull* GetOwningHull() const { return owningHull; }
	void SetOwningHull(UMCPHull* hull);

	TArray<FMCPStat> GetStats() const { return stats; }
	void SetStats(TArray<FMCPStat> newStats);

	UFUNCTION(BlueprintCallable, category = "MCP Hardpoint")
	FMCPStat GetStat(FString name);

protected:
	void UpdateStats();

private:
	void PostEditChangeProperty(struct FPropertyChangedEvent& event) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	UMCPHull* owningHull;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	TArray<FMCPStat> stats;
};
