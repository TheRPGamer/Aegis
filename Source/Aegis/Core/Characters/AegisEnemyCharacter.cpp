// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Characters/AegisPlayerCharacter.h"
#include "Core/AI/AIC/AegisEnemyAIController.h"
#include "Core/Characters/AegisEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AAegisEnemyCharacter::AAegisEnemyCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = GetCapsuleComponent();
    
}

void AAegisEnemyCharacter::PostInitProperties()
{
    Super::PostInitProperties();
}

void AAegisEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Sense();
    Think();
    Act(); 
}

// Called when the game starts or when spawned
void AAegisEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    EnemyState = EAegisEnemyState::Idle;
    // if bPUruse is false, the AI will do nothing
    if(bPursue)
    {
        EnemyState = EAegisEnemyState::Pursuing;
    }
    ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AAegisPlayerCharacter* aegisPlayer = Cast<AAegisPlayerCharacter>(character);
    if(aegisPlayer)
    {
        PlayerTarget = aegisPlayer;
    }
}

void AAegisEnemyCharacter::Sense()
{
   if(PlayerTarget)
   {
       DistanceSqToPlayer = FVector::Dist(GetActorLocation(), PlayerTarget->GetActorLocation());
   }
}

void AAegisEnemyCharacter::Think()
{
    if(IsInHitStun())
    {
        EnemyState = EAegisEnemyState::Staggered;
        return;
    }
    //if montage is null but character is attacking, that means the montage finished playing. Switch to Pursuing
    if(EnemyState == EAegisEnemyState::Attacking && !GetCurrentMontage())
    {
        EnemyState = EAegisEnemyState::Pursuing;
        return;
    }

    //Character is in range to attack
    if(DistanceSqToPlayer <= AttackDistanceSqThreshold && !GetCurrentMontage())
    {
        EnemyState = EAegisEnemyState::InRange;
        return;
    }
    EnemyState = EAegisEnemyState::Pursuing;
}

void AAegisEnemyCharacter::Act()
{
switch(EnemyState)
    {
        case EAegisEnemyState::InRange:
        {
            PlayAnimMontage(AttackMontage1);
            EnemyState = EAegisEnemyState::Attacking;
        }
        case EAegisEnemyState::Pursuing:
        {
            AAegisEnemyAIController*  ac = Cast<AAegisEnemyAIController>(Controller);
            if(ac && PlayerTarget)
            {
                //moves to player
                ac->MoveToActor(PlayerTarget, AttackDistanceSqThreshold - 20.0f, false, true, false, UNavigationQueryFilter::StaticClass());
            }
        }
        default:
        {
            return;
        }
    }
}

