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
		if (character->GetCharacterMovement())
		{
			bIsFalling = character->GetCharacterMovement()->IsFalling();
		}
		MovementSpeed = character->GetVelocity().Size();

		bCanUseMeleeAttack = character->CanUseMeleeAttack();
		bCanUseGuard = character->CanUseGuard(); 
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
