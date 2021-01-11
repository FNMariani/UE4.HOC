// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform_HOC.h"

// Sets default values
APlatform_HOC::APlatform_HOC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PlatformMesh;
}

