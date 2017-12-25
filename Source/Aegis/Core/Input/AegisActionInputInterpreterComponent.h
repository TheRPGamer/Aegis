#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Input/AegisActionInput.h"
#include "Core/Input/Actions/AegisCharacterActions.h"
#include "AegisActionInputInterpreterComponent.generated.h"

USTRUCT()
struct FAegisCharacterInputState
{
    GENERATED_BODY()
    bool bMeleePressed = false;
    bool bRangedPressed = false;
    bool bGuardPressed = false;
    bool bSuperPressed = false;
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisActionInputInterpreterComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UAegisActionInputInterpreterComponent();
    
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnRegister() override;
    
public:
    void Update();
private:
    class AAegisCharacter* GetAegisOwner() const;
    class UAegisActionInputBufferComponent* GetAegisOwnerInputBuffer() const;
};
