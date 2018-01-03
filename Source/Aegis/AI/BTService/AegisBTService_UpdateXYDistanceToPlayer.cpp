// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisBTService_UpdateXYDistanceToPlayer.h"
#include "Core/Characters/AegisPlayerCharacter.h"
#include "Core/Characters/AegisEnemyCharacter.h"
#include "AI/AIC/AegisEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UAegisBTService_UpdateXYDistanceToPlayer::UAegisBTService_UpdateXYDistanceToPlayer()
{
	bCreateNodeInstance = true;
}

void UAegisBTService_UpdateXYDistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	SetBlackboardPlayerTarget(OwnerComp);
}


void UAegisBTService_UpdateXYDistanceToPlayer::SetBlackboardPlayerTarget(UBehaviorTreeComponent& OwnerComp)
{
	auto enemyController = Cast<AAegisEnemyAIController>(OwnerComp.GetAIOwner());
	if (enemyController)
	{
		auto blackboardComp = OwnerComp.GetBlackboardComponent();
		if (blackboardComp)
		{
			auto           player = Cast<AAegisPlayerCharacter>(blackboardComp->GetValue<UBlackboardKeyType_Object>(enemyController->GetPlayerTargetKeyID()));
			auto enemy = Cast<AAegisEnemyCharacter>(enemyController->GetOwner()); 
			float xyDistanceToPlayer = CalculateXYDistanceToPlayer(player, enemy); 
			if (xyDistanceToPlayer > 0.0f)
			{
				blackboardComp->GetValue<UBlackboardKeyType_Object>(enemyController->GetXYDistanceToPlayerKeyID());

			}

		}
	}
}

float UAegisBTService_UpdateXYDistanceToPlayer::CalculateXYDistanceToPlayer(AAegisPlayerCharacter* player, AAegisEnemyCharacter* enemy) const
{
	if (!player || !enemy)
	{
		return -1.0f; 
	}
	FVector playerLocation = player->GetActorLocation();
	FVector enemyLocation = enemy->GetActorLocation();
	//only care about distance in x-y plane. Ignore z 
	playerLocation.Z = 0;
	enemyLocation.Z = 0;
	return FVector::Distance(playerLocation, enemyLocation);
}
