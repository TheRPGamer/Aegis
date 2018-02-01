// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisPhysicalImpactGameplayEffect.h"
#include "Core/Interfaces/AegisPhysicalImpactInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
void UAegisPhysicalImpactGameplayEffect::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    AActor* target = ApplicationInfo.GetApplicationTarget();
    auto interface = Cast<IAegisPhysicalImpactInterface>(target);
    if(interface)
    {
        UE_LOG(AegisGameplayEffectLog, Log, TEXT("Physical Impact Apply"));
        interface->OnPhysicalImpact();
    }
}

