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
	OnActorBeginOverlap.AddDynamic(this, &AAegisWeapon::OnWeaponBeginOverlap); 
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

void AAegisWeapon::OnWeaponBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!bCanDamageTargets || (OtherActor == this) || (OtherActor == Owner) )
	{
		return; 
	}

	auto overlappedTarget = Cast<AAegisCharacter>(OtherActor); 
	if (overlappedTarget)
	{
		overlappedTarget->TakeDamage(Damage, FDamageEvent(), GetController(), Owner); 
	}

}