// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Utility/AegisActionTimeTracker.h"
#include "AegisCharacterGuardLevel.h"
#include "AegisCharacterGuardComponent.generated.h"

/**
* Actor Component responsible for determining the guard level upon guarding, 
* plays the effects associated with teh guard level and affects the owner and attacker according to the guard levels
* @see AegisCharacterGuardLevel 
*/
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterGuardComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAegisCharacterGuardComponent();
	bool IsInGuard() const { return bInGuard; }
	
	/** Function called when Owner begins guarding */
	void OnBeginGuard(); 
	
	/** Function called when the owner stops/is forced to stop guarding */
	void OnEndGuard(); 
	
	/** Function called when the owner's guard volume is hit by an attack */
	float OnAttackImpact(float DamageAmount, const struct FDamageEvent& DamageEvent,
		AController* EventInstigagor, AActor* DamageCauser);
	
	/** Function called when this component is registered */
	virtual void OnRegister() override;

	FName GetGuardLevelName() const { return CurrentGuardLevel.GetName(); }
private: 
	void SetInGuard(bool bInValue) { bInGuard = bInValue; }
	
	/** Applies various Guard Level effects to the owner */
	void DetermineCurrentGuardLevel(); 

	void ApplyGuardLevelEffectsOnOwner();

	/** Applies various effects of guard level to the attacker */
	void ApplyGuardLevelEffectsOnEnemy(AController* EventInstigaor, AActor* DamageCauser);
	
	/** Keeps track of when the owner begins to guard, when the impact occurs and the 
	* time difference between the events 
	**/
	FAegisActionTimeTracker GuardTimeTracker; 
	
	/** Whether the owner of this component is currently in guard state */
	bool bInGuard = false; 
	
	FAegisCharacterGuardLevel CurrentGuardLevel; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardLevels", meta = (AllowPrivateAccess = "true"))
	TArray<FAegisCharacterGuardLevel> GuardLevels; 
};
