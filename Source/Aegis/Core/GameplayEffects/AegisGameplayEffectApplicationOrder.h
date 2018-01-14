// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectTargets.h"
#include "AegisGameplayEffectApplicationOrder.generated.h"

struct FAegisGameplayExecutionInfo;


/**
 * Provides 3 Time Frames for which FAegisGameplayEffectAfftedPrtiesInfo can be specified
 * Gives priorities to when certain effects will fire
 * Execution Order as follows
 * 1. PreExecution
 * 2. Execution
 * 3. Post Execution


 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectApplicationOrder
{
	GENERATED_BODY()
public:
    FAegisGameplayEffectApplicationOrder() { }
    const FAegisGameplayEffectTargets& GetPreEffects() const { return PreEffects; }
    const FAegisGameplayEffectTargets& GetEffects() const { return Effects; }
    const FAegisGameplayEffectTargets& GetPostEffects() const { return PostEffects; }

    
    
    
protected:
    /**
     * Effects that will rum first. Put Cost Effects/Buff Effects etc here first.
     * Anything that takes priority really
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pre-Execution")
    FAegisGameplayEffectTargets PreEffects;
    
    /**
     * Effects that run normally. Damage, knockback, guard break etc
     * should all go here
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Execution")
    FAegisGameplayEffectTargets Effects;
    
    /**
     * Effects that run after the regular course of execution.
     * Additional status effects like Costs, Life Stealing, Buggs etc cacn go here
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Execution")
    FAegisGameplayEffectTargets PostEffects;
};

USTRUCT()
struct AEGIS_API FAegisGameplayEffectTargetsApplierBase
{
    GENERATED_BODY()
public: 
    FAegisGameplayEffectTargetsApplierBase() { }
    virtual ~FAegisGameplayEffectTargetsApplierBase() { }
    virtual void Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ApplicationInfo) const { }
    bool ShouldApplyInstigatorEffects() const { return bApplyInstigatorEffects; }
    void SetApplyInstigatorEffects(bool bInApplyInstigatorEffects) { bApplyInstigatorEffects = bInApplyInstigatorEffects; }
protected:
    bool bApplyInstigatorEffects = false;
    
};


USTRUCT()
struct AEGIS_API FAegisInflicterGameplayEffectTargetsApplier : public FAegisGameplayEffectTargetsApplierBase
{
    GENERATED_BODY()
public:
    FAegisInflicterGameplayEffectTargetsApplier() { }
    void Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ApplicationInfo) const override;
    
};


USTRUCT()
struct AEGIS_API FAegisReceiverGameplayEffectTargetsApplier : public FAegisGameplayEffectTargetsApplierBase
{
    GENERATED_BODY()
public:
    FAegisReceiverGameplayEffectTargetsApplier() { }
    void Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ApplicationInfo) const override;
    
};

