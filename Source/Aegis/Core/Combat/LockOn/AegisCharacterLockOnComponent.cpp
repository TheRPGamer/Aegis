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
    Target = FindClosestTarget();
    State = EAegisCharacterLockOnState::NotMoving; 
}

void UAegisCharacterLockOnComponent::OnEndLockOn()
{
    
}

void UAegisCharacterLockOnComponent::DetermineCurrentState()
{
    ACharacter* owner = Cast<ACharacter>(GetOwner());
  if(!owner)
    {
        return;
    }
    FVector ownerVelocity = owner->GetVelocity();
    
    
}

AActor*UAegisCharacterLockOnComponent:: FindClosestTarget()
{
    TArray<AActor*> result;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UAegisLockOnInterface::StaticClass(), result);
    if(result.Num() < 1 || !GetOwner())
    {
        return nullptr;
    }
    FVector ownerLocation = GetOwner()->GetActorLocation();
    float closestDist = FVector::DistSquared2D(ownerLocation, result[0]->GetActorLocation());
    AActor* closestActor = result[0];
        for(const auto actor : result)
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
