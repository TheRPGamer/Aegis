// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/Effects/AegisGameplayEffectBase.h"
#include "AegisPhysicalImpactGameplayEffect.generated.h"

struct FAegisGameplayEffectApplicationInfo;

/**
 * 
 */

//EditInlineNew allows for unique copy to be created and edited in Properties Window
// Inherited by all child classes by default. Use NoEditInlineNew to override
UCLASS( BlueprintType, Blueprintable)
class AEGIS_API UAegisPhysicalImpactGameplayEffect : public UAegisGameplayEffectBase
{
	GENERATED_BODY()
public:
    virtual void Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const override;
	
};













