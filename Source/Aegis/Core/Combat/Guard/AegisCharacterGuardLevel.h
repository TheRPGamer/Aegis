// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisCharacterGuardLevel.generated.h"

/**
 * A Guard Level with associated requirements for this guard level to be met,
 * Effects to be played  if this guard level is met and the corresponding requirements for this guard level
 * @see AegisCharacterGuardcomponent
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterGuardLevel 
{
	GENERATED_BODY()
public: 
	FName GetName() const { return Name; }
	UParticleSystem* GetParticleEffect() const { return GuardParticleEffect; }
	class USoundCue* GetSoundEffect() const { return GuardSoundEffect; }
	FTimespan GetGuardTicksTimespan() const { return TicksTimespan; }
	float GetDamageReductionMultiplier() const { return DamageReductionMultiplier; }

	/** Returns true if the timespan argument is greather or equal to the lower bound of ticks specified by this Guard Level */
	bool IsTimeSpanGreaterThanLowerBound(FTimespan timespan); 
	
	/** Converts Guard Tick Lower Bound to Timespan */
	void ConvertTicksToTimespan();

	bool operator==(const FAegisCharacterGuardLevel& Other); 

	bool operator!=(const FAegisCharacterGuardLevel& Other);
private: 
	/** Guard Level's Name for quick comparison */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FName Name = NAME_None; 

	/** Guard Level's Display Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FText DisplayName;
	
	/** Particle effect to be played when theis guard level is activated */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* GuardParticleEffect = nullptr; 
	
	/** Sound Effect to be played when this guard level is activated */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	class USoundCue* GuardSoundEffect = nullptr; 
	
	/** Upper Bound of ticks from a character guarding to the point of an attack impact that 
	* qualifies for this guard level.
	* Exposed to designers for easy editing. Will be converted to FTimespan in C++ 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guard Ticks", meta = (AllowPrivateAccess = "true"))
	int32 TicksLowerBound = 0;

	/** Turns Ticks Upper Bound to a FTimespan for fast comparison in Guard Component */
	FTimespan TicksTimespan; 
	
	/** Amount of damage reduction if this guard level was activated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Reduction", meta = (AllowPrivateAccess = "true"))
	float DamageReductionMultiplier = 0.f; 

};
