// Fill out your copyright notice in the Description page of Project Settings.


#include "Key_HOC.h"
#include "Components/SphereComponent.h"

// Sets default values
AKey_HOC::AKey_HOC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootSceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootSceneComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootSceneComponent);
	SphereCollision->InitSphereRadius(32.f);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AKey_HOC::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AKey_HOC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKey_HOC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKey_HOC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Key"));

		PickUpKey();

		Destroy();
	}
}