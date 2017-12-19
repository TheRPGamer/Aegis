// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInputBufferComponent.h"
#include "Core/AegisCharacter.h"


// Sets default values for this component's properties
UAegisActionInputBufferComponent::UAegisActionInputBufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAegisActionInputBufferComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAegisActionInputBufferComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //Increments the Read Index according to the Decay Rate
    Decay();
}

void UAegisActionInputBufferComponent::OnRegister()
{
    InputBuffer.Init(FAegisCharacterActionInput(), BufferSize);
}

void UAegisActionInputBufferComponent::AddActionInput(EAegisCharacterActionType ActionType, bool Pressed)
{
    auto owner = GetAegisOwner();
    if(!owner)
    {
        return;
    }
    if(IsIndexValid(WriteIndex))
    {
        InputBuffer[WriteIndex].Update(owner->GetLockOnState(), ActionType, Pressed);
        IncrementWriteIndex();
    }
}

FAegisCharacterActionInput UAegisActionInputBufferComponent::Get() const
{
    if(IsIndexValid(ReadIndex))
    {
        return InputBuffer[ReadIndex];
    }
    return FAegisCharacterActionInput();
}

void UAegisActionInputBufferComponent::IncrementReadIndex()
{
    //only advance read index if read index is behind write index
    if(ReadIndex != WriteIndex)
    {
        ++ReadIndex;
        ReadIndex %= BufferSize;
    }
}

void UAegisActionInputBufferComponent::IncrementWriteIndex()
{
    ++WriteIndex;
    WriteIndex %= BufferSize;
}

void UAegisActionInputBufferComponent::ResetReadWriteIndices()
{
    ReadIndex = 0;
    WriteIndex = 0;
    //in clears the Action Input on Read Index in case inputs are read to prevent extra actions
    if(InputBuffer.Num() > 0)
    {
        InputBuffer[ReadIndex].Clear(); 
    }
}

bool UAegisActionInputBufferComponent::IsIndexValid(uint32 InIndex) const
{
    if(InIndex < InputBuffer.Num())
    {
        return true;
    }
    return false;
}

void UAegisActionInputBufferComponent::Decay()
{
    ++DecayCounter;
    if(DecayCounter >= DecayRate)
    {
        IncrementReadIndex();
        DecayCounter = 0;
    }
}

AAegisCharacter* UAegisActionInputBufferComponent::GetAegisOwner() const
{
    return Cast<AAegisCharacter>(GetOwner());
}
