// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutor.h"
#include "AegisGameplayEffectBufferComponent.generated.h"

/**
 * Component respondible for processing an Actor's GameplayEffects
*/

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisGameplayEffectBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAegisGameplayEffectBufferComponent();
    void TryExecuteInstigatorEffects(FAegisGameplayEffectTriggerInfo& InTriggerInfo);
    void TryExecuteCauserEffects(FAegisGameplayEffectTriggerInfo& InTriggerInfo);
protected:
    
private:
    void TryExecute(); 
    void Execute();
    void ResetReadWriteIndices(); 
    void IncrementReadIndex();
    void IncrementWriteIndex();
    bool IsIndexValid(uint8 InIndex) const { return InIndex < BufferSize; }
    
    UPROPERTY()
    TArray<FAegisGameplayEffectExecutor> ExecutorBuffer;
    
    const uint8 BufferSize = 50;
    uint8 ReadIndex = 0;
    uint8 WriteIndex = 0;
    bool bInExecution = false; 
    
    
};
