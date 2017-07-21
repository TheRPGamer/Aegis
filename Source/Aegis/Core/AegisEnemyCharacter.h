// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AegisCharacter.h"
#include "AegisEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API AAegisEnemyCharacter : public AAegisCharacter
{
	GENERATED_BODY()
public: 
	explicit AAegisEnemyCharacter(); 
	
	FORCEINLINE UPROPERTY(BlueprintCallable)
	class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
protected: 
	/** Behavior Tree that controls this Enemy Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree = nullptr; 
	
	
	
};
