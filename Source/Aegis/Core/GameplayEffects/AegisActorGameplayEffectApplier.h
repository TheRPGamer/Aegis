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
    void Apply(const FAegisGameplayEffectApplicationOrder& InflicterOrder, const FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo) const;
protected:
    FAegisInflicterGameplayEffectTargetsApplier InflicterApplier;
    FAegisReceiverGameplayEffectTargetsApplier ReceiverApplier;
};

USTRUCT()
struct AEGIS_API FAegisInstigatorGameplayEffectsApplier : public FAegisActorGameplayEffectApplier
{
    GENERATED_BODY()
public:
    FAegisInstigatorGameplayEffectsApplier();
};


USTRUCT()
struct AEGIS_API FAegisCauserGameplayEffectsApplier : public FAegisActorGameplayEffectApplier
{
    GENERATED_BODY()
public:
    FAegisCauserGameplayEffectsApplier();
};












