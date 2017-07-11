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
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh"); 
	if (Mesh)
	{

	}
}

AAegisWeapon::~AAegisWeapon()
{

}

// Called when the game starts or when spawned:AegisPlayerCharacter.cpp
void AAegisWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (Mesh)
	{
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAegisWeapon::OnWeaponBeginOverlap);
	}
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

void AAegisWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCanDamageTargets || (OtherActor == this) || (OtherActor == GetOwner()) )
	{
		return; 
	}

	auto overlappedTarget = Cast<AAegisCharacter>(OtherActor); 
	if (overlappedTarget)
	{
		overlappedTarget->TakeDamage(MeleeAttackDamage, FDamageEvent(), GetController(), GetOwner()); 
	}

}