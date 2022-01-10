// YWA-Interactive. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
  float GetMaxSpeed() const override;

  UPROPERTY(EditAnywhere, Category="Movement", meta=(ClampMin = "1", ClampMax="100"))
  float RunModifier = 1.5;
	
};
