// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataAsset.h"
#include "Containers/Array.h"

#include "MCPStats.generated.h"

USTRUCT()
struct FMCPStat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString name;

	UPROPERTY(EditAnywhere)
	float value;

	UPROPERTY(EditAnywhere)
	bool multiplicative;
};

UCLASS()
class COMPLEXGAMESYSTEMS_API UMCPStats : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FMCPStat> Stats;
};
