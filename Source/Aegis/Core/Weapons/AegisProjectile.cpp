// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisProjectile.h"
#include "Core/GameplayEffects/AegisGameplayEffectTriggerInfo.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionInfo.h"
#include "Core/GameplayEffects/AegisGameplayEffectBufferComponent.h"


// Sets default values
AAegisProjectile::AAegisProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    
    SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
    if(SphereCollisionComponent)
    {
        
        RootComponent = SphereCollisionComponent;
        SphereCollisionComponent->InitSphereRadius(SphereRadius);
        SphereCollisionComponent->bGenerateOverlapEvents = true;
    }
    
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
    if(ProjectileMovementComponent)
    {
        ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
        ProjectileMovementComponent->InitialSpeed = 300.0f;
        ProjectileMovementComponent->MaxSpeed = 300.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f; 
    }
    InitialLifeSpan = LifeSpan;
}

void AAegisProjectile::PostInitProperties()
{
    Super::PostInitProperties(); 
    if(Mesh)
    {
        //Mesh->bGenerateOverlapEvents = true;
        //RootComponent = Mesh;
    }
    
    
    if(SphereCollisionComponent)
    {
        SphereCollisionComponent->SetSphereRadius(SphereRadius  );
    }
    InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AAegisProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAegisProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAegisProjectile::ProcessInstigatorEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo)
{
    
}

void AAegisProjectile::ProcessCauserEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo)
{
    auto gameplayEffectComp = GetGameplayEffectComponent();
    TriggerInfo.ExecutionInfo.Target = this;
    if(gameplayEffectComp)
    {
        gameplayEffectComp->TryExecuteCauserEffects(TriggerInfo);
    }
    auto instigator = Cast<IAegisProcessGameplayEffectInterface>(GetOwner());
    if(instigator)
    {
        TriggerInfo.ExecutionInfo.Target = GetOwner();
        instigator->ProcessInstigatorEffects(TriggerInfo);
    }
    else
    {
        ProcessInstigatorEffects(TriggerInfo); 
    }
    
}

void AAegisProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    FAegisGameplayEffectTriggerInfo trigger;
    trigger.InflictingPartyEffects = GetCurrentExecutionOrder();
    auto target = Cast<IAegisProcessGameplayEffectInterface>(OtherActor);
    if(target)
    {
        trigger.ReceivingPartyEffects = target->GetCurrentExecutionOrder();
    }
    trigger.ExecutionInfo.HitLocation = Hit.Location;
    trigger.ExecutionInfo.HitNormal = Hit.Normal;
    ProcessCauserEffects(trigger);
}


