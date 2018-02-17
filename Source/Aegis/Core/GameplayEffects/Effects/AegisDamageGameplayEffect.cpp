// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisDamageGameplayEffect.h"
#include "Core/Interfaces/AegisDamageInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"

void UAegisDamageGameplayEffect::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    AActor* target = ApplicationInfo.GetApplicationTarget();
    auto interface = Cast<IAegisDamageInterface>(target);
    if(interface)
    {
        UE_LOG(AegisGameplayEffectLog, Log, TEXT("Damage Apply"));
        interface->OnDamage(DamageAmount); 
    }
}

