// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisGameplayEffectChain.generated.h"

struct FAegisGameplayEffectApplicationInfo;
class UAegisGameplayEffectBase;

/**
 * Holds a series of GameplayEffects that will be applied to a single
 * AActor* 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectChain
{
	GENERATED_BODY()
public:
    void Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAegisGameplayEffectBase*> Effects;
};













