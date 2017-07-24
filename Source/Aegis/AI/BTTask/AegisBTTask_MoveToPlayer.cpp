// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AI/BTTask/AegisBTTask_MoveToPlayer.h"
#include "AI/AIC/AegisEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Core/AegisPlayerCharacter.h"

UAegisBTTask_MoveToPlayer::UAegisBTTask_MoveToPlayer()
{

}


EBTNodeResult::Type UAegisBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{ 
	return MoveToPlayer(OwnerComp); 
}

EBTNodeResult::Type UAegisBTTask_MoveToPlayer::MoveToPlayer(UBehaviorTreeComponent& OwnerComp)
{
	auto enemyController = Cast<AAegisEnemyAIController>(OwnerComp.GetAIOwner());
	if (enemyController)
	{
		auto blackboardComp = OwnerComp.GetBlackboardComponent();
		if (blackboardComp)
		{
			auto player = Cast<AAegisPlayerCharacter>(blackboardComp->GetValue<UBlackboardKeyType_Object>(enemyController->GetPlayerTargetKeyID()));
			if (player)
			{
				enemyController->MoveToActor(player, 5.f, true, true, true, 0, true);
				return EBTNodeResult::Succeeded;

			}
		}
	}
	return EBTNodeResult::Failed;
}

