// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisWeapon.h"
#include "AegisPlayerCharacter.h"
#include "AegisEnemyCharacter.h"

// Sets default values
AAegisWeapon::AAegisWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("PawnMesh"); 
	if (Mesh)
	{

	}
}

// Called when the game starts or when spawned
void AAegisWeapon::BeginPlay()
{
	Super::BeginPlay();
	//FIGURE OUT HOW TO USE PHYSICS ASSET COLLISION
	//RootComponent->OnComponentBeginOverlap.AddDynamic(this, &AAegisWeapon::OnWeaponOverlapBegin); 
}

// Called every frame
void AAegisWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAegisWeapon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAegisWeapon::OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCanDamageTargets || (OtherActor == this) || (OtherActor == Owner) ||
		(OtherComponent == nullptr) || (OtherActor == nullptr) )
	{
		return; 
	}

	auto overlappedTarget = Cast<AAegisCharacter>(OtherActor); 
	if (overlappedTarget)
	{
		overlappedTarget->TakeDamage(Damage, FDamageEvent(), GetController(), Owner); 
	}

}