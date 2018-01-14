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
    FORCEINLINE AActor* GetApplicationTarget() const { return ApplicationTarget; }
    FORCEINLINE FVector GetHitLocation() const { return HitLocation; }
    FORCEINLINE FVector GetHitNormal() const { return HitNormal; }
    
    FORCEINLINE void SetApplicationTarget(AActor* InApplicationTarget) { ApplicationTarget = InApplicationTarget; }
    FORCEINLINE void SetHitLocation(const FVector& InHitLocation) { HitLocation = InHitLocation; }
    FORCEINLINE void SetHitNormal(const FVector& InHitNormal ) { HitNormal = InHitNormal; }
private: 
    /** Target to apply GameplayEffects to */
    AActor* ApplicationTarget = nullptr;
    
    FVector HitLocation;
    FVector HitNormal;
    
    
    
    
};













