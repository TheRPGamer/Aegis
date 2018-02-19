// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/Effects/AegisGameplayEffectBase.h"
#include "AegisGuardStunGameplayEffect.generated.h"

struct FAegisGameplayEffectApplicationInfo;

/**
 * 
 */


UCLASS( BlueprintType, Blueprintable, EditInlineNew )
class AEGIS_API UAegisGuardStunGameplayEffect : public UAegisGameplayEffectBase
{
	GENERATED_BODY()
public:
    virtual void Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const override;
	
};













