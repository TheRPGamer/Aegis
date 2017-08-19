// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AegisEnemyAIController.generated.h"

/**
 * Generic Enemy AI Controller
 */
UCLASS()
class AEGIS_API AAegisEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public: 
	AAegisEnemyAIController();

	FORCEINLINE UPROPERTY(BlueprintCallable)
	FName GetPlayerTargetKeyName() const { return PlayerTargetKeyName; }

	FORCEINLINE UPROPERTY(BlueprintCallable)
	uint8 GetPlayerTargetKeyID() const { return PlayerTargetKeyID;  }
	
	FORCEINLINE UPROPERTY(BlueprintCallable)
	FName GetXYDistanceToPlayerKeyName() const { return XYDistanceToPlayerBBKeyName; }

	FORCEINLINE UPROPERTY(BlueprintCallable)
	uint8 GetXYDistanceToPlayerKeyID() const { return XYDistanceToPlayerBBKeyID; }

protected: 
	/** Function called when AI Controller possesses a Pawn */
	virtual void Possess(APawn* InPawn) override;
	
	/** Behavior Tree Component that communicates with Behavior Tree in possessed character */
	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;

	/** Blackboard Component associated with Behavior Tree to store necessary values */
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComponent = nullptr; 

	/** Blackboard Key name for Player Target. NEEDS TO BE SET IN EDITOR */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard Key Names")
	FName PlayerTargetKeyName = NAME_None; 

	/** Blackboard Key ID for Player Target */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard Key IDs")
	uint8 PlayerTargetKeyID = 0; 

	/** Blackboard Key name for Distance To Player. NEEDS TO BE SET IN EDITOR */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard Key Names")
	FName XYDistanceToPlayerBBKeyName = NAME_None;

	/** Blackboard Key ID for Distance To Player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard Key IDs")
	uint8 XYDistanceToPlayerBBKeyID = 0;
	
};
