// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionOrder.h"
#include "AegisProcessGameplayEffectInterface.generated.h"

class UAegisGameplayEffectBufferComponent;
struct FAegisGameplayEffectTriggerInfo;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAegisProcessGameplayEffectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AEGIS_API IAegisProcessGameplayEffectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    FORCEINLINE virtual UAegisGameplayEffectBufferComponent* GetGameplayEffectComponent() const { return nullptr; }
    virtual FAegisGameplayEffectExecutionOrder GetCurrentExecutionOrder() const PURE_VIRTUAL(IAegisProcessGameplayEffectInterface::GetCurrentExecutionOrder, return FAegisGameplayEffectExecutionOrder(); );
    virtual void ProcessInstigatorEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo) PURE_VIRTUAL(IAegisProcessGameplayEffectInterface::ProcessInstigatorEffects, );
    virtual void ProcessCauserEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo) PURE_VIRTUAL(IAegisProcessGameplayEffectInterface::ProcessCauserEffects, );
	
};
