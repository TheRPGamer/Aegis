// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "AegisCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public: 
	explicit UAegisCharacterAnimInstance();
	virtual ~UAegisCharacterAnimInstance();
	
	UFUNCTION(BlueprintCallable)
	void ResetCharacterGroundMeleeState();

	UFUNCTION(BlueprintCallable)
	void ResetCharacterGroundGuardState(); 
	
	UFUNCTION(BlueprintCallable)
	void OnIdleStateReset(); 
protected: 
	void NativeUpdateAnimation(float DeltaSeconds) override; 

private: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true") )
	bool bIsFalling = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 0.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bCanUseMeleeAttack = false; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInGroundMeleeAttack = false; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bCanUseGuard = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInGroundGuard = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInHitStun = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false; 

	
};
