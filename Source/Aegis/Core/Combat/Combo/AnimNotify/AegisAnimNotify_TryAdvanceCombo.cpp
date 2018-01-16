// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_TryAdvanceCombo.h"
#include "Core/AegisCharacterAnimInstance.h"

void UAegisAnimNotify_TryAdvanceCombo::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
    auto character = Cast<AAegisCharacter>(MeshComponent->GetOwner());
    if (character)
	{
		auto comboComp = character->GetComboComponent();
		if (comboComp)
		{
			comboComp->OnComboAnimationEnd(); 
		}
	}
     
    
}



