// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisGameplayEffectExecutor.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionOrder.h"
#include "Core/GameplayEffects/AegisGameplayEffectAffectedPartiesInfo.h"
#include "Core/GameplayEffects/AegisGameplayEffectChain.h"
#include "Core/Characters/AegisCharacter.h"

void FAegisGameplayEffectExecutor::Execute()
{
    if(bInstigator)
    {
        ExecuteInstagatorEffects();
    }
    else
    {
        ExecuteCauserEffects();
    }
}


void FAegisGameplayEffectExecutor::ExecuteInstagatorEffects()
{
    ExecuteInstigatorPreExecutionEffects();
    ExecuteInstigatorExecutionEffects();
    ExecuteInstigatorPostExecutionEffects();
}

void FAegisGameplayEffectExecutor::ExecuteInstigatorPreExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetPreExecutionEffects();
    inflictingPartyInfo.ExecuteInstigatorEffects(executionInfo);
    
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetPreExecutionEffects();
    receivingPartyInfo.ExecuteReceiverEffects(executionInfo);
    
}

void FAegisGameplayEffectExecutor::ExecuteInstigatorExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetExecutionEffects();
    inflictingPartyInfo.ExecuteInstigatorEffects(executionInfo);
    
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetExecutionEffects();
    receivingPartyInfo.ExecuteReceiverEffects(executionInfo);

}

void FAegisGameplayEffectExecutor::ExecuteInstigatorPostExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetPostExecutionEffects();
    inflictingPartyInfo.ExecuteInstigatorEffects(executionInfo);
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetPostExecutionEffects();
    receivingPartyInfo.ExecuteReceiverEffects(executionInfo);
}


void FAegisGameplayEffectExecutor::ExecuteCauserEffects()
{
    ExecuteCauserPreExecutionEffects();
    ExecuteCauserExecutionEffects();
    ExecuteCauserPostExecutionEffects();
}


void FAegisGameplayEffectExecutor::ExecuteCauserPreExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetPreExecutionEffects();
    inflictingPartyInfo.ExecuteCauserEffects(executionInfo);
    
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetPreExecutionEffects();
    receivingPartyInfo.ExecuteTargetEffects(executionInfo);
    
}

void FAegisGameplayEffectExecutor::ExecuteCauserExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetExecutionEffects();
    inflictingPartyInfo.ExecuteCauserEffects(executionInfo);
    
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetExecutionEffects();
    receivingPartyInfo.ExecuteTargetEffects(executionInfo);
    
}

void FAegisGameplayEffectExecutor::ExecuteCauserPostExecutionEffects()
{
    auto& executionInfo = TriggerInfo.ExecutionInfo;
    auto& inflictingPartyInfo = TriggerInfo.InflictingPartyEffects.GetPostExecutionEffects();
    inflictingPartyInfo.ExecuteCauserEffects(executionInfo);
    auto& receivingPartyInfo = TriggerInfo.ReceivingPartyEffects.GetPostExecutionEffects();
    receivingPartyInfo.ExecuteTargetEffects(executionInfo);
}


















