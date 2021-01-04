// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform_HOC.h"

// Sets default values
APlatform_HOC::APlatform_HOC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PlatformMesh;
}

// Called when the game starts or when spawned
void APlatform_HOC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatform_HOC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

