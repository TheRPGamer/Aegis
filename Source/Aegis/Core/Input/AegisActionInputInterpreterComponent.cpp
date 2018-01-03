#include "Aegis.h"
#include "AegisActionInputInterpreterComponent.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Input/AegisActionInputBufferComponent.h"



// Sets default values for this component's properties
UAegisActionInputInterpreterComponent::UAegisActionInputInterpreterComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}


// Called when the game starts
void UAegisActionInputInterpreterComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // ...
    
}


// Called every frame
void UAegisActionInputInterpreterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAegisActionInputInterpreterComponent::OnRegister()
{
    Super::OnRegister();
}

void UAegisActionInputInterpreterComponent::Update()
{
    
}

AAegisCharacter* UAegisActionInputInterpreterComponent::GetAegisOwner() const
{
    return Cast<AAegisCharacter>(GetOwner());
}

UAegisActionInputBufferComponent* UAegisActionInputInterpreterComponent::GetAegisOwnerInputBuffer() const
{
    auto owner = GetAegisOwner();
    if(owner)
    {
        return owner->GetInputBufferComponent();
    }
    return nullptr;
}
