// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "AegisActorGameplayEffectApplier.generated.h"



USTRUCT()
struct AEGIS_API FAegisActorGameplayEffectApplier
{
    GENERATED_BODY()
public:
    FAegisActorGameplayEffectApplier() { }
    virtual ~FAegisActorGameplayEffectApplier() { }
    void Apply(const FAegisGameplayEffectApplicationOrder& InflicterOrder, const FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ExecutionInfo) const;
protected:
    FAegisInflicterGameplayEffectTargetsApplier InflicterExecutor;
    FAegisReceiverGameplayEffectTargetsApplier ReceiverExecutor;
};

USTRUCT()
struct AEGIS_API FAegisInstigatorGameplayEffectsExecutor : public FAegisActorGameplayEffectApplier
{
    GENERATED_BODY()
public:
    FAegisInstigatorGameplayEffectsExecutor();
};


USTRUCT()
struct AEGIS_API FAegisCauserGameplayEffectsExecutor : public FAegisActorGameplayEffectApplier
{
    GENERATED_BODY()
public:
    FAegisCauserGameplayEffectsExecutor();
};












