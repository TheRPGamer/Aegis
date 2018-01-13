// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "AegisGameplayEffectApplicationInfo.generated.h"

USTRUCT()
struct AEGIS_API FAegisGameplayEffectApplicationInfo
{
    GENERATED_BODY()
public:
    FAegisGameplayEffectApplicationInfo() { }

    /** Target to apply GameplayEffects to */
    AActor* Target = nullptr;
    
    FVector HitLocation;
    FVector HitNormal;
    //Add any other variables that would be good to record between effects
    float DamageRecord = 0.f; 
    
    
};













