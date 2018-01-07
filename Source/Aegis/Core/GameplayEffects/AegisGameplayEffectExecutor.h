// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectTriggerInfo.h"
#include "AegisGameplayEffectExecutor.generated.h"

USTRUCT(BlueprintType)
struct FAegisGameplayEffectExecutor
{
    GENERATED_BODY()
public:
    FAegisGameplayEffectExecutor() { }
    void SetTriggerInfo(FAegisGameplayEffectTriggerInfo& InTriggerInfo) { TriggerInfo = InTriggerInfo;}
    void SetIsInstigator(bool InInstagator) { bInstigator = InInstagator; }
    
    void Execute();
    FAegisGameplayEffectTriggerInfo TriggerInfo;
    bool bInstigator = true;
private:
    void ExecuteInstagatorEffects();
    void ExecuteInstigatorPreExecutionEffects();
    void ExecuteInstigatorExecutionEffects();
    void ExecuteInstigatorPostExecutionEffects();
    
    void ExecuteCauserEffects();
    void ExecuteCauserPreExecutionEffects();
    void ExecuteCauserExecutionEffects();
    void ExecuteCauserPostExecutionEffects();
    
};













