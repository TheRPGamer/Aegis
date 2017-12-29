// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_ClosePauseWindow.h"



void UAegisAnimNotify_ClosePauseWindow::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	if (AegisCharacterTarget)
	{
		auto comboComp = AegisCharacterTarget->GetComboComponent(); 
		if (comboComp)
		{
            
		}
	}
}

