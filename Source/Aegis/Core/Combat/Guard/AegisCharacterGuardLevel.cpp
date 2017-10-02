// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterGuardLevel.h"

void FAegisCharacterGuardLevel::ConvertTicksToTimespan()
{
	//Timespan constructor only takes int64
	int64 ticks = static_cast<int64>(TicksLowerBound);
	TicksTimespan = FTimespan(ticks);
}

bool FAegisCharacterGuardLevel::IsTimeSpanGreaterThanLowerBound(FTimespan timespan)
{
	return timespan >= TicksTimespan;
}

bool FAegisCharacterGuardLevel::operator==(const FAegisCharacterGuardLevel& Other)
{
	return GetParticleEffect() == Other.GetParticleEffect() &&
		GetSoundEffect() == Other.GetSoundEffect() &&
		GetGuardTicksTimespan() == Other.GetGuardTicksTimespan() &&
		GetDamageReductionMultiplier() == Other.GetDamageReductionMultiplier(); 
}

bool FAegisCharacterGuardLevel::operator!=(const FAegisCharacterGuardLevel& Other)
{
	return !( (*this) == Other );
}
