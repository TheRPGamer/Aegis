// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGuardStunGameplayEffect.h"
#include "Core/Interfaces/AegisGuardStunInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
void UAegisGuardStunGameplayEffect::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    AActor* target = ApplicationInfo.GetApplicationTarget();
    auto interface = Cast<IAegisGuardStunInterface>(target);
    if(interface)
    {
        UE_LOG(AegisGameplayEffectLog, Log, TEXT("Guard Stun Apply"));
        interface->OnGuardStun();
    }
}

