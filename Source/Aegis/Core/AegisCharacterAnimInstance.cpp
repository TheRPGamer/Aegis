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
		bIsInHitStun = character->IsInHitStun(); 
		bIsDead = false; 
		CurrentComboAnimation = GetComboAnimToPlay();
		bInCombo = IsAegisCharacterInCombo(); 
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


AAegisCharacter* UAegisCharacterAnimInstance::GetAegisCharacter()
{
	auto character =  Cast<AAegisCharacter>(TryGetPawnOwner());
	if (character)
	{
		return character; 
	}
	UE_LOG(AegisComboLog, Log, TEXT("Character Animation instance: unable to get Aegis Character Owner")); 
	return nullptr; 

}


UAegisCharacterComboComponent* UAegisCharacterAnimInstance::GetAegisCharacterComboComponent()
{
	auto character = GetAegisCharacter(); 
	if (character)
	{
		return character->GetComboComponent(); 
	}
	return nullptr; 
}


UAnimSequenceBase* UAegisCharacterAnimInstance::GetComboAnimToPlay()
{
	auto comboComp = GetAegisCharacterComboComponent(); 
	if (comboComp)
	{
		return comboComp->GetAnimation(); 
	}
	return nullptr;
}

bool UAegisCharacterAnimInstance::IsAegisCharacterInCombo() 
{
	auto comboComp = GetAegisCharacterComboComponent(); 
	if (comboComp)
	{
		return comboComp->IsInCombo(); 
	}
	UE_LOG(AegisComboLog, Log, TEXT("Anim Instance cannot access owner Combo Component")); 
	return false; 
}


