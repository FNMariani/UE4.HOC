// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint_HOC.generated.h"

UCLASS()
class UNREALENGINEHOUROFCODE_API ACheckpoint_HOC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint_HOC();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	class USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	UStaticMeshComponent* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	UStaticMeshComponent* Border;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	class USceneComponent* CheckpointTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	class UTextRenderComponent* CheckpointText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	class UArrowComponent* Arrow;


	UPROPERTY()
	UMaterialInstance* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* MaterialInstanceRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckpointEnabled;


	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundCue* CheckpointSound;

private:
	UAudioComponent* CheckpointAudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
