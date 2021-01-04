// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EpicCharacter.generated.h"

UCLASS()
class UNREALENGINEHOUROFCODE_API AEpicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEpicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Handles input for moving forward and backward.
    UFUNCTION()
    void MoveForward(float Value);

    // Handles input for moving right and left.
    UFUNCTION()
    void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCharacter")
	class USpringArmComponent* CameraBoom;//Camera arm assembly

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCharacter")
	class UCameraComponent* FollowCamera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "playerVars")
	float PlayerHealth = 1.f;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
