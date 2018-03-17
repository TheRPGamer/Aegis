// Fill out your copyright notice in the Description page of Project Settings.
#include "Aegis.h"
#include "AegisCharacterLockOnComponent.h"
#include "Core/Interfaces/AegisLockOnInterface.h"
// Sets default values for this component's properties
UAegisCharacterLockOnComponent::UAegisCharacterLockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAegisCharacterLockOnComponent::Update()
{
    
}

void UAegisCharacterLockOnComponent::OnBeginLockOn()
{
    bLockOnPressed = true;
    CurrentTarget = FindClosestTarget();
    OrientOwnerToTarget();
}

void UAegisCharacterLockOnComponent::OnEndLockOn()
{
    CurrentTarget = nullptr;
    bLockOnPressed = false;
}

EAegisCharacterLockOnState UAegisCharacterLockOnComponent::GetState()
{
    ACharacter* owner = Cast<ACharacter>(GetOwner());
  if(!owner || !bLockOnPressed)
    {
        return EAegisCharacterLockOnState::NotLockedOn;
    }
    FVector ownerVelocity = owner->GetVelocity();
    float ownerVelocityMagnitude = ownerVelocity.Size();
    if(ownerVelocityMagnitude <= 0.1f)
    {
        return EAegisCharacterLockOnState::NotMoving;
    }
    ownerVelocity.Normalize();
    FVector ownerForward = owner->GetActorForwardVector();
    ownerForward.Normalize();
    float dot = FVector::DotProduct(ownerVelocity, ownerForward);
    //check if velocity is towards or away from character's forward vector
    return (dot > 0.f) ? EAegisCharacterLockOnState::MovingTowardsTarget : EAegisCharacterLockOnState::MovingAwayFromTarget;

}

AActor*UAegisCharacterLockOnComponent:: FindClosestTarget()
{
    Targets.Empty();
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UAegisLockOnInterface::StaticClass(), Targets);
    if(Targets.Num() < 1 || !GetOwner())
    {
        return nullptr;
    }
    FVector ownerLocation = GetOwner()->GetActorLocation();
    float closestDist = FVector::DistSquared2D(ownerLocation, Targets[0]->GetActorLocation());
    AActor* closestActor = Targets[0];
    //loop through all targets in array and find closest one
    for(const auto actor : Targets)
    {
        float dist = FVector::DistSquared2D(ownerLocation, actor->GetActorLocation());
        if(dist < closestDist)
        {
            closestDist = dist;
            closestActor = actor;
        }
    };

    return closestActor;
}

void UAegisCharacterLockOnComponent::OrientOwnerToTarget() const
{
    ACharacter* owner = Cast<ACharacter>(GetOwner());
    if(!owner || !CurrentTarget)
    {
        return;
    }
    FVector ownerToTarget = CurrentTarget->GetActorLocation() - owner->GetActorLocation();
    ownerToTarget.Normalize();
    //create a rotator with ownerToTarget as forward vector for owner
    FRotator newOwnerRot = FRotationMatrix::MakeFromX(ownerToTarget).Rotator();
    owner->SetActorRotation(newOwnerRot);
}
