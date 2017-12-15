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
	if(GuardLevelsWrapper)
    {
        GuardLevels = GuardLevelsWrapper->GetGuardLevels();
    }
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
    bInGuard = true;
    //Sets the time the action began to now
	GuardTimeTracker.SetActionBeginTime(); 
}

void UAegisCharacterGuardComponent::OnEndGuard()
{
    bInGuard = false;
    GuardTimeTracker.ResetActionTimes();
	//Reset Current Guard Level to default values
    CurrentGuardLevel = FAegisCharacterGuardLevel();
}

float UAegisCharacterGuardComponent::OnAttackImpact(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser) 
{
	//Set action end time to now
	GuardTimeTracker.SetActionEndTime(); 
	DetermineCurrentGuardLevel(); 
    float modifiedDamage = 0.0; 
    //default constructed gurd levle represents "null"
    if(!CurrentGuardLevel.IsDefault())
	{
		modifiedDamage *= CurrentGuardLevel.GetDamageReductionMultiplier(); 
	}
	return modifiedDamage; 
}

void UAegisCharacterGuardComponent::DetermineCurrentGuardLevel()
{
	//if owner has 0 guard levels, this function should not be firing
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
    FAegisCharacterGuardLevel guardLevel;
    //Guard Levels sorted in ascending Lower Bounds
    for(int i=0; i<GuardLevels.Num(); ++i)
    {
        guardLevel = GuardLevels[i];
        //if guard time span < lower bound of current guard level
        //since lower bounds are in ascending order, we overshot the correct guard level by 1
        //therefore GuardLevels[i-1] is the guard level we're actually in
        if(!guardLevel.IsTimeSpanGreaterThanLowerBound(guardTimespan))
        {
            CurrentGuardLevel = GuardLevels[i-1];
            return;
        }
    }
    //if execution reaches here, that means
    //guard time span > lower bound of last Guard level.
    //i.e GuardLevels[size -1] is the one we're supposed to be at
    CurrentGuardLevel = GuardLevels[GuardLevels.Num()-1];
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
