// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_HOC.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINEHOUROFCODE_API AGameMode_HOC : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	FTransform spawnLocation;
};
