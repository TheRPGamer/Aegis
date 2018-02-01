// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActorGameplayEffectApplier.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

void FAegisActorGameplayEffectApplier::Apply(const FAegisGameplayEffectApplicationOrder& InflicterOrder, const FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    //Apply PreEffects
    InflicterApplier.Apply(InflicterOrder.GetPreEffects(), ApplicationInfo);
    ReceiverApplier.Apply(ReceiverOrder.GetPreEffects(), ApplicationInfo);
    //Apply Effects
    InflicterApplier.Apply(InflicterOrder.GetEffects(), ApplicationInfo);
    ReceiverApplier.Apply(ReceiverOrder.GetEffects(), ApplicationInfo);
    //Apply Post Effects
    InflicterApplier.Apply(InflicterOrder.GetPostEffects(), ApplicationInfo);
    ReceiverApplier.Apply(ReceiverOrder.GetPostEffects(), ApplicationInfo);
}


FAegisInstigatorGameplayEffectsApplier::FAegisInstigatorGameplayEffectsApplier()
{
    InflicterApplier.SetApplyInstigatorEffects(true);
    ReceiverApplier.SetApplyInstigatorEffects(true);
}


FAegisCauserGameplayEffectsApplier::FAegisCauserGameplayEffectsApplier()
{
    InflicterApplier.SetApplyInstigatorEffects(false);
    ReceiverApplier.SetApplyInstigatorEffects(false);
}









