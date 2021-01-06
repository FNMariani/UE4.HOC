// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_HOC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void AGameMode_HOC::BeginPlay()
{
	Super::BeginPlay();

	//Timer

	//HUD

	//Get PlayerStart
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	spawnLocation = FoundActors[0]->GetActorTransform();

	//Respawn
}