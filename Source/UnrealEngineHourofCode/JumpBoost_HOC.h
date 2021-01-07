// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpBoost_HOC.generated.h"

UCLASS()
class UNREALENGINEHOUROFCODE_API AJumpBoost_HOC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpBoost_HOC();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	class USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	class UTextRenderComponent* JumpText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	class URotatingMovementComponent* RotatingComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float JumpVelocity = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float DefaultJumpVelocity = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float CoolDownTime = 4.f;

	//Sound
	UPROPERTY()
	class USoundCue* JumpPowerUpSound;

	UPROPERTY()
	UAudioComponent* JumpPowerUpSoundAudioComponent;


	UPROPERTY()
	class AEpicCharacter* EpicCharacter;

	/* Handle to manage the timer */
	FTimerHandle TimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ResetPowerUp();
};
