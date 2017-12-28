// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AegisCharacterLockOnComponent.generated.h"

/**
 * Component responsible for keeping track of an AegisCharacter's Lock On defails

*/

UENUM()
enum class EAegisCharacterLockOnState : uint8
{
    //Char Locked On && Velocity Vector Toward Target
    MovingTowardsTarget,
    //Char Locked On && Velocity Vector Away From Target
    MovingAwayFromTarget,
    //Char Locked On && Char not moving
    NotMoving,
    //Char not locked on and not moving
    NotLockedOn
};


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterLockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAegisCharacterLockOnComponent();
	

};
