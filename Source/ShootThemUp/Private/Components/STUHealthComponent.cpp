// YWA-Interactive. All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(DamageDevSphere, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUHealthComponent::BeginPlay() {
  Super::BeginPlay();
  Health = MaxHealth;

  OnHealthChanged.Broadcast(Health);
  
  AActor* ComponentOwner = GetOwner();

  if (ComponentOwner) ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::HandleTakeAnyDamage);
  
}

void USTUHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser) {
  
  if (Damage <= 0 || IsDead()) return;

  Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
  OnHealthChanged.Broadcast(Health);

  if (IsDead()) {
   OnDeath.Broadcast(); 
  }
}