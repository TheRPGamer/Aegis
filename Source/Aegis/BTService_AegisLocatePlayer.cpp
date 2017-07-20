// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "BTService_AegisLocatePlayer.h"
#include "AegisEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AegisPlayerCharacter.h"

UBTService_AegisLocatePlayer::UBTService_AegisLocatePlayer()
{
	bCreateNodeInstance = true; 
}

void UBTService_AegisLocatePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	SetBlackboardPlayerTarget(OwnerComp); 
}

void UBTService_AegisLocatePlayer::SetBlackboardPlayerTarget(UBehaviorTreeComponent& OwnerComp)
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
