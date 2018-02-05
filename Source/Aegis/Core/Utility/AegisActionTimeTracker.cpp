// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionTimeTracker.h"

void FAegisActionTimeTracker::SetActionBeginTime()
{
	ActionBeginTime = FDateTime::Now();
}

void FAegisActionTimeTracker::SetActionEndTime()
{
	ActionEndTime = FDateTime::Now();
}

void FAegisActionTimeTracker::CalculateTimeDifference()
{
	if (ActionEndTime <= ActionBeginTime)
	{
		return; 
	}
	TimeDifference = FTimespan(ActionEndTime.GetTicks()) - FTimespan(ActionBeginTime.GetTicks()); 
}

void FAegisActionTimeTracker::ResetActionTimes()
{
	ActionBeginTime = FDateTime::MinValue(); 
	ActionEndTime = FDateTime::MinValue(); 
	TimeDifference = FTimespan::Zero(); 
}
