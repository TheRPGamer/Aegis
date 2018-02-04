// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
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
	FORCEINLINE FName GetName() const { return Name; }
	FORCEINLINE FTimespan GetGuardTicksTimespan() const { return TicksTimespan; }
    FORCEINLINE FAegisGameplayEffectApplicationOrder GetGuardGFX() const { return GuardGFX; }

	/** Returns true if the timespan argument is greather or equal to the lower bound of ticks specified by this Guard Level */
	bool IsTimeSpanGreaterThanLowerBound(FTimespan timespan); 
    /** Returns true if members are the same as default constructed Guard Level*/
    bool IsDefault();
    
	/** Converts Guard Tick Lower Bound to Timespan */
	void ConvertTicksToTimespan();

	//Begin Debug Functionality
    void SetName(FName InName) { Name = InName; }
    int32 GetLowerBound() const { return TicksLowerBound; }
    void SetLowerBound(int32 InLowerBound) {TicksLowerBound = InLowerBound; }
    void SetGuardGFX(FAegisGameplayEffectApplicationOrder& InGuardGFX) { GuardGFX = InGuardGFX; }
    //End Debug Functionality
    bool operator==(const FAegisCharacterGuardLevel& Other);
    bool operator!=(const FAegisCharacterGuardLevel& Other); 
private: 
	/** Guard Level's Name for quick comparison */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FName Name = NAME_None; 

	/** Guard Level's Display Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FText DisplayName;
	
	/** Upper Bound of ticks from a character guarding to the point of an attack impact that 
	* qualifies for this guard level.
	* Exposed to designers for easy editing. Will be converted to FTimespan in C++ 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guard Ticks", meta = (AllowPrivateAccess = "true"))
	int32 TicksLowerBound = 0;

	/** Turns Ticks Upper Bound to a FTimespan for fast comparison in Guard Component */
	FTimespan TicksTimespan;
    
    /** Gameplay Effects to be applied when this Guard Level is activated  */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Effects", meta = (AllowPrivateAccess = "true"))
    FAegisGameplayEffectApplicationOrder GuardGFX;
	
	

};
