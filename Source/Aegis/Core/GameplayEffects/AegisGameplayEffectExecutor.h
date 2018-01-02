// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AegisGameplayEffectExecutor.generated.h"

class UAegisGameplayEffectBase;

/**
 * In charge of executing the associated effect if all requirements are met
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectExecutor
{
	GENERATED_BODY()
public:
    void TryExecute(AActor* Target);
protected:
    
    UPROPERTY()
    UAegisGameplayEffectBase* Effect = nullptr;
	//Requirements the Target must be in to Execute
};













