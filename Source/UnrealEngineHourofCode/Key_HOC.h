// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Key_HOC.generated.h"

UCLASS()
class UNREALENGINEHOUROFCODE_API AKey_HOC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKey_HOC();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	class USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	class USphereComponent* SphereCollision;

	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
	void PickUpKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
