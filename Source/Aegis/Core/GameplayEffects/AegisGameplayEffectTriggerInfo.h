// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionOrder.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionInfo.h"
#include "AegisGameplayEffectTriggerInfo.generated.h"

/**
 * Info struct used to hold information about the parties involved in the Gameplay Effect
 * The impact position of the effect, hit normals etc
 */
USTRUCT()
struct AEGIS_API FAegisGameplayEffectTriggerInfo
{
	GENERATED_BODY()
public:
    /** Execution Order of Instigator and Causer */
    FAegisGameplayEffectExecutionOrder InflictingPartyEffects;
    
    /** Execution Order of Receiver and Target */
    FAegisGameplayEffectExecutionOrder ReceivingPartyEffects;
    
    FAegisGameplayEffectExecutionInfo ExecutionInfo;
    
    
};













