// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin_HOC.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ACoin_HOC::ACoin_HOC()
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

	CoinText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CoinText"));
	CoinText->SetupAttachment(RootSceneComponent);
	CoinText->SetText(TEXT("Coin Pickup"));
	CoinText->SetHorizontalAlignment(EHTA_Center);

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");

	static ConstructorHelpers::FObjectFinder<USoundCue> CoinSoundObject(TEXT("SoundCue'/Game/Hour_of_Code/Audio/SFX_coin.SFX_coin'"));
	if (CoinSoundObject.Succeeded())
	{
		CoinSound = CoinSoundObject.Object;

		CoinSoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CoinSoundAudioComponent"));
		CoinSoundAudioComponent->SetupAttachment(RootComponent);

		CoinSoundAudioComponent->bAutoActivate = false;
		CoinSoundAudioComponent->bStopWhenOwnerDestroyed = false;
	}


	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin_HOC::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACoin_HOC::BeginPlay()
{
	Super::BeginPlay();

	if (CoinSoundAudioComponent && CoinSound)
	{
		CoinSoundAudioComponent->SetSound(CoinSound);
	}
}

// Called every frame
void ACoin_HOC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin_HOC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Coin"));
		if (CoinSoundAudioComponent && CoinSound)
		{
			CoinSoundAudioComponent->Play(0.f);
		}
		Destroy();
	}
}