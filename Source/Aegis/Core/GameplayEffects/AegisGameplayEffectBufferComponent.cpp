// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectBufferComponent.h"

// Sets default values for this component's properties
UAegisGameplayEffectBufferComponent::UAegisGameplayEffectBufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAegisGameplayEffectBufferComponent::TryExecuteInstigatorEffects(FAegisGameplayEffectTriggerInfo& InTriggerInfo)
{
    if(IsIndexValid(WriteIndex))
    {
        ExecutorBuffer[WriteIndex].SetTriggerInfo(InTriggerInfo);
        ExecutorBuffer[WriteIndex].SetIsInstigator(true);
        IncrementWriteIndex();
        TryExecute();
        
    }
}

void UAegisGameplayEffectBufferComponent::TryExecuteCauserEffects(FAegisGameplayEffectTriggerInfo& InTriggerInfo)
{
    if(IsIndexValid(WriteIndex))
    {
        ExecutorBuffer[WriteIndex].SetTriggerInfo(InTriggerInfo);
        ExecutorBuffer[WriteIndex].SetIsInstigator(false);
        IncrementWriteIndex();
        TryExecute();
        
    }
}

void UAegisGameplayEffectBufferComponent::TryExecute()
{
    if(!bInExecution)
    {
        Execute();
    }
}

void UAegisGameplayEffectBufferComponent::Execute()
{
    bInExecution = true;
    while(ReadIndex < WriteIndex)
    {
        if(IsIndexValid(ReadIndex))
        {
            ExecutorBuffer[ReadIndex].Execute();
        }
        IncrementReadIndex();
    }
    ResetReadWriteIndices();
    bInExecution = false;
}

void UAegisGameplayEffectBufferComponent::ResetReadWriteIndices()
{
    WriteIndex = 0;
    ReadIndex = 0;
}

void UAegisGameplayEffectBufferComponent::IncrementReadIndex()
{
    ++ReadIndex;
    ReadIndex %= BufferSize;
}

void UAegisGameplayEffectBufferComponent::IncrementWriteIndex()
{
    ++WriteIndex;
    WriteIndex %= BufferSize;
}
