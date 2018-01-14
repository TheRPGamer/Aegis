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
    void ApplyInstigatorEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { InstigatorEffects.Apply(ApplicationInfo); }
    void ApplyCauserEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { CauserEffects.Apply(ApplicationInfo); }
    void ApplyReceiverEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { ReceiverEffects.Apply(ApplicationInfo); }
    void ApplyTargetEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { TargetEffects.Apply(ApplicationInfo); }



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
















