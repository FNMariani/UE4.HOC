// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform_HOC.generated.h"

UCLASS()
class UNREALENGINEHOUROFCODE_API APlatform_HOC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatform_HOC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	UStaticMeshComponent* PlatformMesh;
};
