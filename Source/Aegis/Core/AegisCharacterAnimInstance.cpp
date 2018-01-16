// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacterAnimInstance.h"
#include "Core/Characters/AegisCharacter.h"
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

void UAegisCharacterAnimInstance::PlayComboAnimation(UAnimSequenceBase* Animation)
{
    if(!Animation)
    {
        return; 
    }
    auto character = GetAegisCharacter();
    if(character)
    {
        auto mesh = character->GetMesh();
        if(mesh)
        {
            //IMPORTANT:removes control from AnimBP/AnimInstance
            //sets USkeletalMeshComponent's EAnimationMode to AnimationSingleNode by default
            mesh->PlayAnimation(Animation, false);
        }
    }
}

