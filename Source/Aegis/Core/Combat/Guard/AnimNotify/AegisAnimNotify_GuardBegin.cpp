// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_GuardBegin.h"

void UAegisAnimNotify_GuardBegin::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
	if (AegisCharacterTarget)
	{
		auto guardComp = AegisCharacterTarget->GetGuardComponent();
		if (guardComp)
		{
            guardComp->OnBeginGuard();
		}
	}
}



