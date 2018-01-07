// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionOrder.h"
#include "AegisGameplayEffectExecutionInfo.generated.h"

USTRUCT()
struct FAegisGameplayEffectExecutionInfo
{
    GENERATED_BODY()
public:
    FAegisGameplayEffectExecutionInfo() { }
    AActor* Target = nullptr;
    FVector HitLocation;
    FVector HitNormal;
    //Add any other variables that would be good to record between effects
    float DamageRecord = 0.f; 
    
    
};













