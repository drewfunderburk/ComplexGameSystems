// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "MCPStats.h"

#include "MCPHardpoint.generated.h"


class UMCPHull;
UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
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
	// Getters and Setters
	UMCPStats* GetMCPStatsAsset() const { return statsAsset; }
	void SetMCPStatsAsset(UMCPStats* asset);

	TArray<FMCPHardpointStat> GetStats() const { return stats; }

	// Get stat by name
	UFUNCTION(BlueprintCallable, Category = "MCP Hardpoint")
	FMCPHardpointStat GetStat(FString name);

	UFUNCTION(BlueprintCallable, Category = "MCP Hardpoint")
	void SetStat(FString name, float value, bool isMultiplicative);

protected:
	void UpdateStats();

private:
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true"))
	UMCPStats* statsAsset;

public:
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, Category = "MCP Hardpoint", meta = (AllowPrivateAccess = "true", TitleProperty = "Name"))
	TArray<FMCPHardpointStat> stats;
};
