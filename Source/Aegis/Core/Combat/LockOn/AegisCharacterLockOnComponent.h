// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AegisCharacterLockOnComponent.generated.h"

/**
 * Component responsible for keeping track of an AegisCharacter's Lock On details

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
    
    FORCEINLINE AActor* GetTarget() const { return CurrentTarget; }
    virtual void Update();
    virtual void OnBeginLockOn();
    virtual void OnEndLockOn();
    
    /** Based on Owner's movement etc, determine  current Lock On State*/
    EAegisCharacterLockOnState GetState();
protected:
    /** Find the closest AActor to be the new Lock On Target */
    AActor* FindClosestTarget();
    
    /** Orient Owner to Current Target */
    void OrientOwnerToTarget() const; 
    /** Array of all Actors in Range. Used in determining closest actor  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<AActor*> Targets;
    /** The current Actor being Locked On To. The Target should have the IAegisLockOn interface*/
    UPROPERTY()
    AActor* CurrentTarget = nullptr;
    EAegisCharacterLockOnState State = EAegisCharacterLockOnState::NotLockedOn;
    
    bool bLockOnPressed = false; 
};
