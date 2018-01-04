// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AegisBTService_UpdatePlayerTarget.generated.h"

/**
 * BT Node to Locate the Player Character
 */
UCLASS()
class AEGIS_API UAegisBTService_UpdatePlayerTarget : public UBTService
{
	GENERATED_BODY()
public: 
	explicit UAegisBTService_UpdatePlayerTarget();

	/** Called every tick interval */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected: 
	/** If the player character exists, update the Blackboard with its reference */
	virtual void SetBlackboardPlayerTarget(UBehaviorTreeComponent& OwnerComp); 
	
};
