// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisGameplayEffectChain.generated.h"

class UAegisGameplayEffectBase;
struct FAegisGameplayEffectExecutionInfo; 
/**
 * 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectChain
{
	GENERATED_BODY()
public:
    void Execute(FAegisGameplayEffectExecutionInfo& ExecutionInfo) const; 
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAegisGameplayEffectBase*> Effects;
};













