// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisProcessGameplayEffectInterface.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
#include "Core/GameplayEffects/AegisActorGameplayEffectApplier.h"


// Add default functionality here for any IKnockbackEffectInterface functions that are not pure virtual.

void IAegisProcessGameplayEffectInterface::ApplyInstigatorGameplayEffects(const FAegisGameplayEffectApplicationOrder& InflicterOrder, FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo)
{
    FAegisInstigatorGameplayEffectsApplier gfxApplier;
    gfxApplier.Apply(InflicterOrder, ReceiverOrder, ApplicationInfo);
}

void IAegisProcessGameplayEffectInterface::ApplyCauserGameplayEffects(const FAegisGameplayEffectApplicationOrder& InflicterOrder, FAegisGameplayEffectApplicationOrder& ReceiverOrder, FAegisGameplayEffectApplicationInfo& ApplicationInfo)
{
    FAegisCauserGameplayEffectsApplier gfxApplier;
    gfxApplier.Apply(InflicterOrder, ReceiverOrder, ApplicationInfo);
    
}

void IAegisProcessGameplayEffectInterface::ApplyGameplayEffects(AActor* Inflicter, AActor* Receiver, FAegisGameplayEffectApplicationInfo& ApplicationInfo)
{
    if(!Inflicter || !Receiver)
    {
        return;
    }
    FAegisGameplayEffectApplicationOrder inflicterOrder;
    FAegisGameplayEffectApplicationOrder receiverOrder;
    //if the inflicter has this interface, grab the relevant Application ORder
    auto inflicterInterface = Cast<IAegisProcessGameplayEffectInterface>(Inflicter);
    if(inflicterInterface)
    {
        inflicterOrder = inflicterInterface->GetCurrentApplicationOrder();
    }
    //if the receiver has this interface, grab the current application order
    auto receiverInterface = Cast<IAegisProcessGameplayEffectInterface>(Receiver);
    if(receiverInterface)
    {
        receiverOrder = receiverInterface->GetCurrentApplicationOrder();
    }
    ApplicationInfo.SetApplicationTarget(Inflicter);
    ApplyCauserGameplayEffects(inflicterOrder, receiverOrder, ApplicationInfo);
    /* Ignore Instigator Effects for now
    AActor* instigator = Inflicter->GetOwner();
    //if inflicter's owner has this interface, it's the instigator
    //else the Inflicter is both Causer and Instigator
    auto instigatorInterface = Cast<IAegisProcessGameplayEffectInterface>(instigator);
    if(instigatorInterface)
    {
        ApplicationInfo.SetApplicationTarget(instigator);
    }
    ApplyInstigatorGameplayEffects(inflicterOrder, receiverOrder,
     ApplicationInfo);
     */
}

