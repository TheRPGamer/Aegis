// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectChain.h"
#include "AegisGameplayEffectTargets.generated.h"



struct FAegisGameplayEffectApplicationInfo;
class UAegisGameplayEffectBase;

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
    //Begin Debug Functions

    FORCEINLINE void AddInstigatorEffect(UAegisGameplayEffectBase* InEffect) { InstigatorEffects.Add(InEffect); }
    FORCEINLINE void AddCauserEffect(UAegisGameplayEffectBase* InEffect) { CauserEffects.Add(InEffect); }
    FORCEINLINE void AddReceiverEffect(UAegisGameplayEffectBase* InEffect) { ReceiverEffects.Add(InEffect); }
    FORCEINLINE void AddTargetEffect(UAegisGameplayEffectBase* InEffect) { TargetEffects.Add(InEffect); }


    //End Debug Functions
    
    FORCEINLINE void ApplyInstigatorEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { InstigatorEffects.Apply(ApplicationInfo); }
    FORCEINLINE void ApplyCauserEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { CauserEffects.Apply(ApplicationInfo); }
    FORCEINLINE void ApplyReceiverEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { ReceiverEffects.Apply(ApplicationInfo); }
    FORCEINLINE void ApplyTargetEffects(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { TargetEffects.Apply(ApplicationInfo); }



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
















