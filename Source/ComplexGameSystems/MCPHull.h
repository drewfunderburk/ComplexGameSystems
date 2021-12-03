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
	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	UMCPStats* GetBaseStats() const { return m_BaseStats; }
	TMap<FString, float> GetStats() const { return m_Stats; }

	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	TArray<UMCPHardpoint*> GetHardpoints() const { return m_Hardpoints; }
	UFUNCTION(BlueprintCallable, category = "MCP Hull")
	float GetStat(FString name);

private:
	UPROPERTY(EditAnywhere, category = "MCP Hull")
	UMCPStats* m_BaseStats;
	TMap<FString, float> m_Stats;
	UPROPERTY(EditAnywhere, category = "MCP Hull")
	TArray<UMCPHardpoint*> m_Hardpoints;		
};
