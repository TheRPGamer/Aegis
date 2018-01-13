// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActorGameplayEffectApplier.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

void FAegisActorGameplayEffectApplier::Apply(const FAegisGameplayEffectApplicationOrder& InflicterOrder, const FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ExecutionInfo) const
{
    //Apply PreEffects
    InflicterExecutor.Apply(InflicterOrder.GetPreEffects(), ExecutionInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetPreEffects(), ExecutionInfo);
    //Apply Effects
    InflicterExecutor.Apply(InflicterOrder.GetEffects(), ExecutionInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetEffects(), ExecutionInfo);
    //Apply Post Effects
    InflicterExecutor.Apply(InflicterOrder.GetPostEffects(), ExecutionInfo);
    ReceiverExecutor.Apply(ReceiverOrder.GetPostEffects(), ExecutionInfo);
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









