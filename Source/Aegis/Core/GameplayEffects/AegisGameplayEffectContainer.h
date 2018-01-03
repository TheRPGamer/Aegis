// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectChain.h"
#include "AegisGameplayEffectContainer.generated.h"


/**
 * Container that holds Effect Chains that will affect all parties involved in a effect event
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisGameplayEffectContainer
{
	GENERATED_BODY()
public:
    const FAegisGameplayEffectChain& GetInstigatorChain() const { return InstigatorChain; }
    const FAegisGameplayEffectChain& GetCauserChain() const { return CauserChain; }
    const FAegisGameplayEffectChain& GetReceiverChain() const { return ReceiverChain; }
    const FAegisGameplayEffectChain& GetTargetChain() const { return TargetChain; }
    
protected:
    /** Effects that apply to the Instigator of the effect event*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instigator Effects")
    FAegisGameplayEffectChain InstigatorChain;
    
    /** Effects that apply to the Causer of the effect event*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Causer Effects")
    FAegisGameplayEffectChain CauserChain;
    
    /** Effects that apply to the Receiver of the effectevent */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Receiver Effects")
    FAegisGameplayEffectChain ReceiverChain;
    
    /** Effects that apply to the Target of the effectevent */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Effects")
    FAegisGameplayEffectChain TargetChain;
};













