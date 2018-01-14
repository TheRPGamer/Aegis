// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActorGameplayEffectApplier.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

void FAegisActorGameplayEffectApplier::Apply(const FAegisGameplayEffectApplicationOrder& InflicterOrder, const FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    //Apply PreEffects
    InflicterExecutor.Apply(InflicterOrder.GetPreEffects(), ApplicationInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetPreEffects(), ApplicationInfo);
    //Apply Effects
    InflicterExecutor.Apply(InflicterOrder.GetEffects(), ApplicationInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetEffects(), ApplicationInfo);
    //Apply Post Effects
    InflicterExecutor.Apply(InflicterOrder.GetPostEffects(), ApplicationInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetPostEffects(), ApplicationInfo);
}


FAegisInstigatorGameplayEffectsExecutor::FAegisInstigatorGameplayEffectsExecutor()
{
    InflicterExecutor.SetApplyInstigatorEffects(true);
    ReceiverExecutor.SetApplyInstigatorEffects(true);
}


FAegisCauserGameplayEffectsExecutor::FAegisCauserGameplayEffectsExecutor()
{
    InflicterExecutor.SetApplyInstigatorEffects(false);
    ReceiverExecutor.SetApplyInstigatorEffects(false);
}









