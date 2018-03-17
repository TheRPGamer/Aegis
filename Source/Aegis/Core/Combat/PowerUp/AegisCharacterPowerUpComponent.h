// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AegisCharacterPowerUpComponent.generated.h"

/**
 * Component that augments the effects of a Character's Action
*/

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAegisCharacterPowerUpComponent();
private:
};
