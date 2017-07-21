// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AI/AIC/AegisEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Core/AegisEnemyCharacter.h"

AAegisEnemyAIController::AAegisEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent"); 

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent"); 
}

void AAegisEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn); 
	auto enemyCharacter = Cast<AAegisEnemyCharacter>(InPawn); 
	if (enemyCharacter && BlackboardComponent && BehaviorTreeComponent)
	{
		BlackboardComponent->InitializeBlackboard(*enemyCharacter->GetBehaviorTree()->BlackboardAsset); 
		PlayerTargetKeyID = BlackboardComponent->GetKeyID(PlayerTargetKeyName); 
		BehaviorTreeComponent->StartTree(*(enemyCharacter->GetBehaviorTree()), EBTExecutionMode::Looped); 
	}
}


