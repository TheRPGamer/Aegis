// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboComponent.h"

// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAegisCharacterComboComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAegisCharacterComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAegisCharacterComboComponent::ProcessPlayerInput(FName InputName)
{
	TArray<UAegisCharacterCombo*> possibleCombos = OwnerCurrentCombo->GetPossibleCombosFromInput(InputName); 
	if (possibleCombos.Num() == 0)
	{
		return; 
	}
	for (auto& combo : possibleCombos)
	{
		//there should only be ONE combo that matches. Therefore, just get the first one
		if(OwnerCurrentComboState.Matches(combo->GetComboState()))
		{
			OwnerCurrentCombo = combo; 
			break; 
		}
	}
}

