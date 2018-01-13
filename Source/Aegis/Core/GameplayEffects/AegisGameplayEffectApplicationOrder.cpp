// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectApplicationOrder.h"

void FAegisInflicterGameplayEffectTargetsApplier::Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ExecutionInfo) const
{
    if(ShouldApplyInstigatorEffects())
    {
        Targets.ApplyInstigatorEffects(ExecutionInfo);
    }
    else
    {
        Targets.ApplyCauserEffects(ExecutionInfo);
    }
}


void FAegisReceiverGameplayEffectTargetsApplier::Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ExecutionInfo) const
{
    if(ShouldApplyInstigatorEffects())
    {
        Targets.ApplyReceiverEffects(ExecutionInfo);
    }
    else
    {
        Targets.ApplyTargetEffects(ExecutionInfo);
    }
}
