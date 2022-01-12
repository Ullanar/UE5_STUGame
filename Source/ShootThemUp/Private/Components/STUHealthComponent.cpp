// YWA-Interactive. All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUHealthComponent::BeginPlay() {
  Super::BeginPlay();
  Health = MaxHealth;

  AActor* ComponentOwner = GetOwner();

  if (ComponentOwner) ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::HandleTakeAnyDamage);
  
}

void USTUHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser) {

  Health -= Damage;
}