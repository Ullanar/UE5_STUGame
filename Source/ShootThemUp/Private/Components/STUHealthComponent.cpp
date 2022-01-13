// YWA-Interactive. All Rights Reserved.

#include "Components/STUHealthComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay() {
  Super::BeginPlay();
  SetHealth(MaxHealth);

  AActor* ComponentOwner = GetOwner();

  if (ComponentOwner)
    ComponentOwner->OnTakeAnyDamage.AddDynamic(
        this, &USTUHealthComponent::HandleTakeAnyDamage);
}

void USTUHealthComponent::HealUpdate() {
  SetHealth(Health + HealModifier);

  if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld()) {
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
  }
}

void USTUHealthComponent::SetHealth(float NewHealth) {
  Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
  OnHealthChanged.Broadcast(Health);
}

void USTUHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor,
                                              float Damage,
                                              const UDamageType* DamageType,
                                              AController* InstigatedBy,
                                              AActor* DamageCauser) {
  if (Damage <= 0 || IsDead() || !GetWorld()) return;

  SetHealth(Health - Damage);

  GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

  if (IsDead()) {
    OnDeath.Broadcast();
  } else if (IsAutoHealEnabled) {
    GetWorld()->GetTimerManager().SetTimer(
        HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime,
        true, HealStartDelayAfterGetDamage);
  }
}
