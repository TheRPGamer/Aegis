// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AegisBTTask_MoveToPlayer.generated.h"

/**
 * BT Task Node that moves AI Character to Player Character's location if Player Character exists
 */
UCLASS()
class AEGIS_API UAegisBTTask_MoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public: 
	explicit UAegisBTTask_MoveToPlayer();

	/** Called when behavior tree eexecution reaches the BP node*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected: 
	/** If the player character exists, move to its location*/
	virtual EBTNodeResult::Type MoveToPlayer(UBehaviorTreeComponent& OwnerComp); 

	
	
	
};
