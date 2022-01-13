// YWA-Interactive. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter {
  GENERATED_BODY()

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  USpringArmComponent* SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UCameraComponent* CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  USTUHealthComponent* HealthComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
  UTextRenderComponent* HealthTextComponent;

  UPROPERTY(EditDefaultsOnly, Category="Animation")
  UAnimMontage* DeathAnimMontage;

  UPROPERTY(EditDefaultsOnly, Category="Movement");
  FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

  UPROPERTY(EditDefaultsOnly, Category="Movement");
  FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

public:
  ASTUBaseCharacter(const FObjectInitializer& ObjInit);

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;

  UFUNCTION(BlueprintCallable, Category="Movement")
  bool IsRunning() const;

  UFUNCTION(BlueprintCallable, Category="Movement")
  float GetMovementDirection() const;

private:
  bool IsPlayerWantsToRun = false;
  bool IsMovingForward = false;

  void MoveForward(float Amount);
  void MoveRight(float Amount);
  void OnStartRunning();
  void OnStopRunning();

  void OnDeath();
  void OnHealthChanged(float Health);

  UFUNCTION()
  void OnGroundLanded(const FHitResult& Hit);
};
