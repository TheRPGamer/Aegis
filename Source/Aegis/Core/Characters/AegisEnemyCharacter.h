// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Weapons/AegisProjectile.h"

//Interfaces
#include "Core/Interfaces/AegisLockOnInterface.h"
#include "AegisEnemyCharacter.generated.h"


class AAegisPlayerCharacter;
/**
 * 
 */
UENUM()
enum class EAegisEnemyState : uint8
{
    Idle,
    Pursuing,
    InRange,
    Attacking,
    Staggered
};


UCLASS()
class AEGIS_API AAegisEnemyCharacter : public AAegisCharacter, public IAegisLockOnInterface
{
	GENERATED_BODY()
public:
    AAegisEnemyCharacter();
    virtual void PostInitProperties() override;
    virtual void Tick(float DeltaTime) override;
protected:
    virtual void BeginPlay() override;
public:
    
	FORCEINLINE UPROPERTY(BlueprintCallable)
	class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
    
    


protected:
    /** First step in AI Tick. Updates variables by sensing surroundings*/
    virtual void Sense();
    
    /** Second step in AI Tick. Processes sensed data and makes decisions */
    virtual void Think();
    
    /** Final step in AI Tick. Acts based on the decisions made in Think()  */
    virtual void Act();
    

    /** Player target */
    UPROPERTY()
    AAegisPlayerCharacter* PlayerTarget = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackDistanceSqThreshold = 0.f;
    
    float DistanceSqToPlayer = 0.f;

    EAegisEnemyState EnemyState = EAegisEnemyState::Idle;

    UPROPERTY(EditAnywhere, BLueprintReadWrite)
    bool bPursue = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montages")
    UAnimMontage* AttackMontage1 = nullptr;
    
	/** Behavior Tree that controls this Enemy Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree = nullptr; 
	
	
	
};
