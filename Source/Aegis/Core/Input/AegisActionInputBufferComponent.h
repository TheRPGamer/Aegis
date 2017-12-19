// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Input/AegisActionInput.h"
#include "AegisActionInputBufferComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisActionInputBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAegisActionInputBufferComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnRegister() override; 

    void AddActionInput(EAegisCharacterActionType ActionType, bool Pressed);
    FAegisCharacterActionInput Get() const;
private:
    void IncrementReadIndex();
    void IncrementWriteIndex();
    void ResetReadWriteIndices();
    bool IsIndexValid(uint32 InIndex) const;
    void Decay(); 
    class AAegisCharacter* GetAegisOwner() const;
    
    UPROPERTY()
    TArray<FAegisCharacterActionInput> InputBuffer;
    
    uint32 ReadIndex = 0;
    uint32 WriteIndex = 0;
    uint32 DecayRate = 10;
    uint32 DecayCounter = 0;
    uint32 BufferSize = 60; 
};
