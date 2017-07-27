// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/AegisCharacterCombo.h"
#include "AegisCharacterComboComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	explicit UAegisCharacterComboComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Based on the Input pressed, transition to a new combo if need be */
	void ProcessPlayerInput(FName InputName);

	void SetIsInAir(bool IsInAir) { OwnerCurrentComboState.bIsInAir = IsInAir; }
	void SetIsInSuperMode(bool bIsInSuperModde) { OwnerCurrentComboState.bIsInSuperMode = bIsInSuperModde; }
	void SetLockOnState(EAegisCharacterLockOnState LockOnState) { OwnerCurrentComboState.LockOnState = LockOnState; }
private: 
	/** The Character Owner's current Combo State. Determines what Combos can be transitioned to */
	struct FAegisCharacterComboState OwnerCurrentComboState; 
	
	/**The Character Owner's Current Combo */
	class UAegisCharacterCombo* OwnerCurrentCombo = nullptr;

		
	
};
