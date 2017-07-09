// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterAnimInstance.h"
#include "AegisCharacter.h"

UAegisCharacterAnimInstance::UAegisCharacterAnimInstance()
{

}
																																																																																																																																																																																											
UAegisCharacterAnimInstance::~UAegisCharacterAnimInstance()
{

}

void UAegisCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		bIsFalling = character->IsInAir(); 
		MovementSpeed = character->GetVelocity().Size();
		bCanUseMeleeAttack = character->CanUseMeleeAttack();
		bIsInGroundMeleeAttack = character->IsInGroundMeleeAttack(); 
		bCanUseGuard = character->CanUseGuard(); 
		bIsInGroundGuard = character->IsInGroundGuard(); 
		bIsInHitStun = character->IsInHitStun(); 
		bIsDead = character->IsDead(); 
	}
}

void UAegisCharacterAnimInstance::ResetCharacterGroundMeleeState()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner()); 
	if (character)
	{
		character->ResetGroundMeleeAttackState(); 
	}
}

void UAegisCharacterAnimInstance::ResetCharacterGroundGuardState()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		character->ResetGroundGuardState(); 
	}

}


void UAegisCharacterAnimInstance::OnIdleStateReset()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		character->IdleStateReset();
	}

}
