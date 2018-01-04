// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisBTService_UpdatePlayerTarget.h"
#include "Core/AI/AIC/AegisEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Core/Characters/AegisPlayerCharacter.h"

UAegisBTService_UpdatePlayerTarget::UAegisBTService_UpdatePlayerTarget()
{
	bCreateNodeInstance = true; 
}

void UAegisBTService_UpdatePlayerTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	SetBlackboardPlayerTarget(OwnerComp); 
}

void UAegisBTService_UpdatePlayerTarget::SetBlackboardPlayerTarget(UBehaviorTreeComponent& OwnerComp)
{
	auto enemyController = Cast<AAegisEnemyAIController>(OwnerComp.GetAIOwner());
	if (enemyController)
	{
		auto world = GetWorld();
		APlayerController* playerController = nullptr;
		if (world)
		{
			playerController = world->GetFirstPlayerController();
		}
		AAegisPlayerCharacter* player = nullptr;
		if (playerController)
		{
			player = Cast<AAegisPlayerCharacter>(playerController->GetPawn());
		}

		if (player)
		{
			auto blackboardComp = OwnerComp.GetBlackboardComponent();
			if (blackboardComp)
			{
				blackboardComp->SetValue<UBlackboardKeyType_Object>(enemyController->GetPlayerTargetKeyID(), player);
			}
		}
	}
}
