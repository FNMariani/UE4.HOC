// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpBoost_HOC.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "EpicCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AJumpBoost_HOC::AJumpBoost_HOC()
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

	JumpText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("JumpText"));
	JumpText->SetupAttachment(RootSceneComponent);
	JumpText->SetText(TEXT("Jump Boost"));
	JumpText->SetHorizontalAlignment(EHTA_Center);

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");

	static ConstructorHelpers::FObjectFinder<USoundCue> JumpPowerUpSoundObject(TEXT("SoundCue'/Game/Hour_of_Code/Audio/SFX_jump_boost.SFX_jump_boost'"));
	if (JumpPowerUpSoundObject.Succeeded())
	{
		JumpPowerUpSound = JumpPowerUpSoundObject.Object;

		JumpPowerUpSoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("JumpPowerUpSoundAudioComponent"));
		JumpPowerUpSoundAudioComponent->SetupAttachment(RootComponent);

		JumpPowerUpSoundAudioComponent->bAutoActivate = false;
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AJumpBoost_HOC::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AJumpBoost_HOC::BeginPlay()
{
	Super::BeginPlay();
	
	if (JumpPowerUpSoundAudioComponent && JumpPowerUpSound)
	{
		JumpPowerUpSoundAudioComponent->SetSound(JumpPowerUpSound);
	}
}

void AJumpBoost_HOC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		EpicCharacter = Cast<AEpicCharacter>(OtherActor);

		if (EpicCharacter != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jump Booster ON"));

			EpicCharacter->GetCharacterMovement()->JumpZVelocity = JumpVelocity;

			Mesh->ToggleVisibility(false);
			SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (JumpPowerUpSoundAudioComponent && JumpPowerUpSound)
			{
				JumpPowerUpSoundAudioComponent->Play(0.f);
			}

			JumpBoostOn();

			//Delay
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJumpBoost_HOC::ResetPowerUp, CoolDownTime, false);
		}
	}
}

void AJumpBoost_HOC::ResetPowerUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jump Booster OFF"));

	Mesh->ToggleVisibility(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EpicCharacter->GetCharacterMovement()->JumpZVelocity = DefaultJumpVelocity;

	JumpBoostOff();

	// Ensure the timer is cleared by using the timer handle
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}