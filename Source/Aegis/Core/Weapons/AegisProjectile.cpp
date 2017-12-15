// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisProjectile.h"


// Sets default values
AAegisProjectile::AAegisProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

