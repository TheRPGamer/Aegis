// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectChain.h"
#include "Core/GameplayEffects/AegisGameplayEffectBase.h"

void FAegisGameplayEffectChain::Execute(FAegisGameplayEffectExecutionInfo& InExecutionInfo) const
{
    for(auto& effect : Effects)
    {
        effect->Execute(InExecutionInfo);
    }
}
