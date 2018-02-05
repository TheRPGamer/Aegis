// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterGuardLevel.h"

void FAegisCharacterGuardLevel::ConvertTicksToTimespan(float TickScaleFactor)
{
	//Timespan constructor only takes int64
	int64 ticks = static_cast<int64>(TicksLowerBound);
    ticks *= TickScaleFactor;
	TicksTimespan = FTimespan(ticks);
}

bool FAegisCharacterGuardLevel::IsTimeSpanGreaterThanLowerBound(FTimespan timespan)
{
	return timespan >= TicksTimespan;
}

bool FAegisCharacterGuardLevel::operator==(const FAegisCharacterGuardLevel& Other)
{
    return false;
}
bool FAegisCharacterGuardLevel::IsDefault()
{
    return false;
}

bool FAegisCharacterGuardLevel::operator!=(const FAegisCharacterGuardLevel& Other)
{
    return !(*this == Other);
}

