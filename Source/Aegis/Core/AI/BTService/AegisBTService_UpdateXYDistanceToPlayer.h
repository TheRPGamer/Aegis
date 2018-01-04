// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AegisBTService_UpdateXYDistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisBTService_UpdateXYDistanceToPlayer : public UBTService
{
	GENERATED_BODY()
public: 
	explicit UAegisBTService_UpdateXYDistanceToPlayer();
	
protected: 
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; 

	void SetBlackboardPlayerTarget(UBehaviorTreeComponent& OwnerComp); 
	float CalculateXYDistanceToPlayer(class AAegisPlayerCharacter* player, class AAegisEnemyCharacter* enemy) const; 
	
};
