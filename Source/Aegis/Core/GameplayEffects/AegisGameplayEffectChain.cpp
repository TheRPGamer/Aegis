// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectChain.h"
#include "Core/GameplayEffects/Effects/AegisGameplayEffectBase.h"

void FAegisGameplayEffectChain::Apply(FAegisGameplayEffectApplicationInfo& ApplicationInfo) const
{
    for(auto& effect : Effects)
    {
        if(effect)
        {
            effect->Apply(ApplicationInfo);
        }
    }
}
