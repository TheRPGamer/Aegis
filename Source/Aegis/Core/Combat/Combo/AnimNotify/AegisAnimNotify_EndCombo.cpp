// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_EndCombo.h"
#include "Core/Characters/AegisCharacter.h"

void UAegisAnimNotify_EndCombo::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
	if (AegisCharacterTarget)
	{
		auto comboComp = AegisCharacterTarget->GetComboComponent(); 
		if (comboComp)
		{
			comboComp->SetInCombo(false); 
		}
	}
}


