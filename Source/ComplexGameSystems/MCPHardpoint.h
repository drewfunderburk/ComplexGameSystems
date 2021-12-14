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

	TArray<FMCPStat> GetStats() const { return stats; }
	void SetStats(TArray<FMCPStat> newStats);

	UFUNCTION(BlueprintCallable, category = "MCP Hardpoint")
	FMCPStat GetStat(FString name);

protected:
	void UpdateStats();

private:
	void BeginDestroy() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

public:
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	TArray<FMCPStat> stats;
};
