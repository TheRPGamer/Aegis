// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "AegisProcessGameplayEffectInterface.generated.h"

class UAegisGameplayEffectBufferComponent;
struct FAegisGameplayEffectEvent;
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
    virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const PURE_VIRTUAL(IAegisProcessGameplayEffectInterface::GetCurrentApplicationOrder, return FAegisGameplayEffectApplicationOrder(); );
    virtual void ApplyInstigatorGameplayEffects(const FAegisGameplayEffectApplicationOrder& Inflicter, FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo);
    virtual void ApplyCauserGameplayEffects(const FAegisGameplayEffectApplicationOrder& Inflicter, FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo);

    
	
};




