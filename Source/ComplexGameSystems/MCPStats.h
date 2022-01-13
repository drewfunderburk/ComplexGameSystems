// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Array.h"
#include "Containers/Map.h"

#include "MCPStats.generated.h"

// Used for MCPStats data assets only
USTRUCT(BlueprintType)
struct FMCPDataAssetStat
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";
};

// Used for stats in MCPHull objects
USTRUCT(BlueprintType)
struct FMCPHullStat
{
	GENERATED_USTRUCT_BODY()
public:
	FMCPHullStat(FString name = "", float value = 0.0f)
		: Name(name), Value(value) {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.0f;
};

// Used for stats in MCPHardpoint objects
USTRUCT(BlueprintType)
struct FMCPHardpointStat
{
	GENERATED_USTRUCT_BODY()
public:
	FMCPHardpointStat(FString name = "", float value = 0.0f, bool isMultiplicative = false) 
		: Name(name), Value(value), IsMultiplicative(isMultiplicative) {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMultiplicative = false;
};

// Type used for MCPStats Data Assets
UCLASS()
class COMPLEXGAMESYSTEMS_API UMCPStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MCP Stats", meta = (TitleProperty = "Name"))
	TArray<FMCPDataAssetStat> Stats;
};
