// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutor.h"
#include "AegisGameplayEffectChain.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectChain
{
	GENERATED_BODY()
public:
    void Execute(AActor* Target); 
protected:
    UPROPERTY()
    TArray<FAegisGameplayEffectExecutor> Effects;
};













