// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AegisGameplayEffectComponent.generated.h"

/**
 * Component respondible for processing an Actor's GameplayEffects
*/

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisGameplayEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAegisGameplayEffectComponent();
	

};
