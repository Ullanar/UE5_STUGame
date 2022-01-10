// YWA-Interactive. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
  
public:
  ASTUBaseCharacter(const FObjectInitializer& ObjInit);

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
