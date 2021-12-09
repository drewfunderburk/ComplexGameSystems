// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Array.h"

#include "MCPStats.generated.h"

USTRUCT(BlueprintType)
struct FMCPDataAssetStat
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";
};

USTRUCT(BlueprintType)
struct FMCPStat
{
	GENERATED_USTRUCT_BODY()
public:
	FMCPStat() {}
	FMCPStat(FString name) { Name = name; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMultiplicative = true;
};

UCLASS()
class COMPLEXGAMESYSTEMS_API UMCPStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "MCP Stats")
	TArray<FMCPDataAssetStat> Stats;
};
