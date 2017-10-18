// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterGuardComponent.h"
#include "Core/AegisCharacter.h"

// Sets default values for this component's properties
UAegisCharacterGuardComponent::UAegisCharacterGuardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAegisCharacterGuardComponent::OnRegister()
{
	Super::OnRegister();
	//Converts the number of ticks designers gave the Guard levels to Timespans
	for (auto& guardLevel : GuardLevels)
	{
		guardLevel.ConvertTicksToTimespan();
	}
	//sort the Guard Levels according to Timespan in ascending order
	auto ascendingSortLambda = [](const FAegisCharacterGuardLevel& LHS, const FAegisCharacterGuardLevel& RHS)
	{
		return LHS.GetGuardTicksTimespan() < RHS.GetGuardTicksTimespan();
	};
	GuardLevels.Sort(ascendingSortLambda);
}

void UAegisCharacterGuardComponent::OnBeginGuard()
{
	//Sets the time the action began to now
	GuardTimeTracker.SetActionBeginTime(); 
}

void UAegisCharacterGuardComponent::OnEndGuard()
{
	GuardTimeTracker.ResetActionTimes(); 
	CurrentGuardLevel = FAegisCharacterGuardLevel();
}

float UAegisCharacterGuardComponent::OnAttackImpact(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser) 
{
	//Set action end time to now
	GuardTimeTracker.SetActionEndTime(); 
	DetermineCurrentGuardLevel(); 
	float modifiedDamage = DamageAmount;  
	//if current guard level is not  null as represented as default constructed guard level *
	if (CurrentGuardLevel != FAegisCharacterGuardLevel())
	{
		modifiedDamage *= CurrentGuardLevel.GetDamageReductionMultiplier(); 
	}
	return modifiedDamage; 
}

void UAegisCharacterGuardComponent::DetermineCurrentGuardLevel()
{
	//if .there are 0 guard levels, this function shouldn't even be firing
	if (GuardLevels.Num() < 1)
	{
		auto owner = Cast<AAegisCharacter>(GetOwner());
		if (owner)
		{
			UE_LOG(AegisGuardLog, Error, TEXT("%s has empty Guard Levels but is trying to use guard. Fix in editor."), *(owner->GetHumanReadableName()))
		}
		return;
	}
	//Calculate time difference from character starting to guard to attack impact
	GuardTimeTracker.CalculateTimeDifference();
	FTimespan guardTimespan = GuardTimeTracker.GetTimeDifference(); 
	FAegisCharacterGuardLevel currentGuardLevel;
	//if there's only 1 guard level
	if (GuardLevels.Num() == 1)
	{
		currentGuardLevel = GuardLevels[0]; 
		//if the calculated time span > the lower bound time requirement of the single guard level 
		// Set CurrentGuardLevel to the guardLevel
		if (currentGuardLevel.IsTimeSpanGreaterThanLowerBound(guardTimespan)) 
		{
			CurrentGuardLevel = currentGuardLevel;
		}
		//guard levle requirements not met. Reset Current Guard level
		else
		{
			CurrentGuardLevel = FAegisCharacterGuardLevel();
		}
		return; 
	}
	//there's more than 1 guard level, we need to look at all of them to see where we're at 
	for (int i = 0; i < GuardLevels.Num(); ++i)
	{
		currentGuardLevel = GuardLevels[i];
		//Guard Levels is sorted in ascending order . If the predicate function returns false, 
		//It means that the guardTimespan < currentGuardLevel's time requirements, therefore GuradLevel prior to 
		//currentGuardLevel is the correct GuardLevel the character has met 
		if (!currentGuardLevel.IsTimeSpanGreaterThanLowerBound(guardTimespan))
		{
			CurrentGuardLevel = GuardLevels[i - 1]; 
			return; 
		}
	}
	//if execution reaches here, there's a problem. 
	//That means the guard timespan is 
	CurrentGuardLevel = FAegisCharacterGuardLevel(); 
	//Reached the end of the GuardLevels list and still can't find a match. This can't be correct 
	auto owner = Cast<AAegisCharacter>(GetOwner());
	if(owner)
	{ 
		//log problem
	}
}

void UAegisCharacterGuardComponent::ApplyGuardLevelEffectsOnOwner()
{
	auto owner = Cast<AAegisCharacter>(GetOwner());
	if (owner)
	{
		UE_LOG(AegisGuardLog, Error, TEXT("%s guard timespan did not match any assigned Guard Levels."), *(owner->GetHumanReadableName()));
	}
}

void UAegisCharacterGuardComponent::ApplyGuardLevelEffectsOnEnemy(AController* EventInstigator, AActor* DamageCauser)
{

}