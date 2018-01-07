// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectAffectedPartiesInfo.h"
#include "AegisGameplayEffectExecutionOrder.generated.h"

/**
 * Struct that holds effects in their execution order
 * Aimed to give Designers complete control over when certain effects need to happen
 * IN the course of a Move/Attack/Event
 
 
 
 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectExecutionOrder
{
	GENERATED_BODY()
public:
    const FAegisGameplayEffectAffectedPartiesInfo& GetPreExecutionEffects() const { return PreExecutionEffects; }
    const FAegisGameplayEffectAffectedPartiesInfo& GetExecutionEffects() const { return ExecutionEffects; }
    const FAegisGameplayEffectAffectedPartiesInfo& GetPostExecutionEffects() const { return PostExecutionEffects; }
    
    /**
     * Effects that will rum first. Put Cost Effects/Buff Effects etc here first.
     * Anything that takes priority really
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pre-Execution")
    FAegisGameplayEffectAffectedPartiesInfo PreExecutionEffects;
    
    /**
     * Effects that run normally. Damage, knockback, guard break etc
     * should all go here
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Execution")
    FAegisGameplayEffectAffectedPartiesInfo ExecutionEffects;
    
    /**
     * Effects that run after the regular course of execution.
     * Additional status effects like Costs, Life Stealing, Buggs etc cacn go here
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Execution")
    FAegisGameplayEffectAffectedPartiesInfo PostExecutionEffects;
};













