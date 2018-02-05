// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisActionTimeTracker.generated.h"
/**
 * Utility struct meant to keep track of when a certain action is performed and when the action should end
 * Also provides functions to caluclate time difference between the actions and reset the action times 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisActionTimeTracker
{
	GENERATED_BODY()
public:
	FTimespan GetTimeDifference() const { return TimeDifference; }
	FTimespan GetTimeDifference() { return TimeDifference; }
    
    FDateTime GetActionBeginTime() const { return ActionBeginTime; }
    
    FDateTime GetActionEndTime() const { return ActionEndTime; }

	/** Sets Action Begin Time To Current Time */
	void SetActionBeginTime(); 
	
	/** Sets Action End Time To Current Time */
	void SetActionEndTime(); 
	
	/** Calculates teh time difference between the Action Begin and end times */
	void CalculateTimeDifference();

	/** Resets all the Action Times */
	void ResetActionTimes(); 

private: 
	FDateTime ActionBeginTime = FDateTime::MinValue(); 
	FDateTime ActionEndTime = FDateTime::MinValue(); 
	FTimespan TimeDifference = FTimespan::Zero();
};
