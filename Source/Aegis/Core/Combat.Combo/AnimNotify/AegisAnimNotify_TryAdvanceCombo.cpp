// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_TryAdvanceCombo.h"

void UAegisAnimNotify_TryAdvanceCombo::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
	if (AegisCharacterTarget)
	{
		auto comboComp = AegisCharacterTarget->GetComboComponent(); 
		if (comboComp)
		{
			comboComp->OnComboAnimationEnd(); 
		}
	}
}



