// YWA-Interactive. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent {
  GENERATED_BODY()

public:
  USTUHealthComponent();
  float GetHealth() const { return Health; }

  UFUNCTION(BlueprintCallable)
  bool IsDead() const {return Health <= 0;}

  FOnDeath OnDeath;
  FOnHealthChanged OnHealthChanged;
  
protected:
  virtual void BeginPlay() override;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin = "0", ClampMax="1000"))
  float MaxHealth = 100;

private:
  float Health = 0;

  UFUNCTION()
void HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
                         const class UDamageType* DamageType,
                         class AController* InstigatedBy,
                         AActor* DamageCauser);
};
