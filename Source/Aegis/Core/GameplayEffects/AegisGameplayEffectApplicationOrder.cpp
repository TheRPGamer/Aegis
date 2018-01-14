// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectApplicationOrder.h"

void FAegisInflicterGameplayEffectTargetsApplier::Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    if(ShouldApplyInstigatorEffects())
    {
        Targets.ApplyInstigatorEffects(ApplicationInfo);
    }
    else
    {
        Targets.ApplyCauserEffects(ApplicationInfo);
    }
}


void FAegisReceiverGameplayEffectTargetsApplier::Apply(const FAegisGameplayEffectTargets& Targets,FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    if(ShouldApplyInstigatorEffects())
    {
        Targets.ApplyReceiverEffects(ApplicationInfo);
    }
    else
    {
        Targets.ApplyTargetEffects(ApplicationInfo);
    }
}
