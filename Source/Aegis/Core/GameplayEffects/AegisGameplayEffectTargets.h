// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectChain.h"
#include "AegisGameplayEffectTargets.generated.h"



struct FAegisGameplayEffectApplicationInfo;

/**
 * Holds the GameplayEffectChains that need to be applied to various Actors
 * When a move/action is performed at a certain time
 */

USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectTargets
{
	GENERATED_BODY()
public:
    FAegisGameplayEffectTargets() { }
    void ApplyInstigatorEffects(FAegisGameplayEffectApplicationInfo& ExecutionInfo) const { InstigatorEffects.Apply(ExecutionInfo); }
    void ApplyCauserEffects(FAegisGameplayEffectApplicationInfo& ExecutionInfo) const { CauserEffects.Apply(ExecutionInfo); }
    void ApplyReceiverEffects(FAegisGameplayEffectApplicationInfo& ExecutionInfo) const { ReceiverEffects.Apply(ExecutionInfo); }
    void ApplyTargetEffects(FAegisGameplayEffectApplicationInfo& ExecutionInfo) const { TargetEffects.Apply(ExecutionInfo); }



protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisGameplayEffectChain InstigatorEffects;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisGameplayEffectChain CauserEffects;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisGameplayEffectChain ReceiverEffects;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisGameplayEffectChain TargetEffects;
};
















