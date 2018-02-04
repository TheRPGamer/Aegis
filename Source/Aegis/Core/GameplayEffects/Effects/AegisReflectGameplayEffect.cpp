// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisReflectGameplayEffect.h"
#include "Core/Interfaces/AegisReflectInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
void UAegisReflectGameplayEffect::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    AActor* target = ApplicationInfo.GetApplicationTarget();
    auto interface = Cast<IAegisReflectInterface>(target);
    if(interface)
    {
        UE_LOG(AegisGameplayEffectLog, Log, TEXT("Reflect Apply"));
        interface->OnReflect();
    }
}

