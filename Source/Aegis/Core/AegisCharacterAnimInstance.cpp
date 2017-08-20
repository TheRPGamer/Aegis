// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacterAnimInstance.h"
#include "Core/AegisCharacter.h"
#include "Core/AegisWeapon.h"
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
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
		//bIsDead = character->IsDead(); 
		bIsDead = false; 
		CurrentMeleeAnimation = GetMeleeAnimToPlay(); 
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


void UAegisCharacterAnimInstance::MakeCharacterWeaponActive()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character && character->GetEquippedWeapon())
	{
		character->GetEquippedWeapon()->SetCanDamageTargetsTrue();
	}

}



void UAegisCharacterAnimInstance::MakeCharacterWeaponInactive()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character && character->GetEquippedWeapon())
	{
		character->GetEquippedWeapon()->SetCanDamageTargetsFalse();
	}

}


void UAegisCharacterAnimInstance::ResetCharacterHitStunState()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		character->ResetHitStunState();
	}

}


UAnimationAsset* UAegisCharacterAnimInstance::GetMeleeAnimToPlay()
{
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		auto comboComp = character->GetComboComponent(); 
		if (comboComp)
		{
			return comboComp->GetAnimation(); 
		}
	}
	return nullptr; 
}