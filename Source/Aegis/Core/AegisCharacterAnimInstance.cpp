// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacterAnimInstance.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
void UAegisCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto character = Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		bFalling = character->IsInAir();
		MovementSpeed = character->GetVelocity().Size();
		bInHitStun = character->IsInHitStun();
		bDead = false;
        CurrentComboAnimation = GetComboAnim();
		bInCombo = IsAegisCharacterInCombo(); 
		bTransitionOutOfCombo = !IsAegisCharacterInCombo(); 
	}
}


UAegisCharacterComboComponent* UAegisCharacterAnimInstance::GetAegisCharacterComboComponent() const
{
	auto character = GetAegisCharacter(); 
	if (character)
	{
		return character->GetComboComponent(); 
	}
	return nullptr; 
}


UAnimSequenceBase* UAegisCharacterAnimInstance::GetComboAnim() const
{
	auto comboComp = GetAegisCharacterComboComponent(); 
	if (comboComp)
	{
		return comboComp->GetCurrentAnimation();
	}
	return nullptr;
}

bool UAegisCharacterAnimInstance::IsAegisCharacterInCombo() const
{
	auto comboComp = GetAegisCharacterComboComponent(); 
	if (comboComp)
	{
		return comboComp->IsInCombo(); 
	}
	UE_LOG(AegisComboLog, Log, TEXT("Anim Instance cannot access owner Combo Component")); 
	return false; 
}


