// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisKnockbackGameplayEffect.h"
#include "Core/Interfaces/AegisKnockbackInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"

void UAegisKnockbackGameplayEffect::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    AActor* target = ApplicationInfo.GetApplicationTarget();
    auto interface = Cast<IAegisKnockbackInterface>(target);
    if(interface)
    {
        UE_LOG(AegisGameplayEffectLog, Log, TEXT("Knockback Apply"));
        interface->OnKnockback(ApplicationInfo.GetHitNormal(), KnockbackMagnitude); 
    }
}

