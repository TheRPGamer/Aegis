// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/Effects/AegisGameplayEffectBase.h"
#include "AegisKnockbackGameplayEffect.generated.h"

struct FAegisGameplayEffectApplicationInfo;

/**
 * 
 */

UCLASS( BlueprintType, Blueprintable)
class AEGIS_API UAegisKnockbackGameplayEffect : public UAegisGameplayEffectBase
{
	GENERATED_BODY()
public:
    virtual void Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const override;
	
};













