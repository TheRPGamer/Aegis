// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_OpenPauseWindow.h"

void UAegisAnimNotify_OpenPauseWindow::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
	if (AegisCharacterTarget)
	{
		auto comboComp = AegisCharacterTarget->GetComboComponent(); 
		if (comboComp)
		{
            
		}
	}
}



