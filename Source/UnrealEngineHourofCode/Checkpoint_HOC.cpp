// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint_HOC.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ACheckpoint_HOC::ACheckpoint_HOC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootSceneComponent;

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(RootSceneComponent);
	
	Border = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Border"));
	Border->SetupAttachment(Button);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootSceneComponent);
	SphereCollision->InitSphereRadius(32.f);

	CheckpointTransform = CreateDefaultSubobject<USceneComponent>(TEXT("CheckpointTransform"));

	CheckpointText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CheckpointText"));
	CheckpointText->SetupAttachment(RootSceneComponent);
	CheckpointText->SetText(TEXT("Checkpoint"));
	CheckpointText->SetHorizontalAlignment(EHTA_Center);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootSceneComponent);


	//Dynamic Material
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mat(TEXT("MaterialInstanceConstant'/Game/Hour_of_Code/Materials/MI_Checkpoint.MI_Checkpoint'"));
	if (Mat.Object != NULL)
	{
		Material = Mat.Object;
	}

	if (Material)
	{
		MaterialInstanceRef = UMaterialInstanceDynamic::Create(Material, this, TEXT("DynamicMaterial"));
	}


	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint_HOC::OnOverlapBegin);


	static ConstructorHelpers::FObjectFinder<USoundCue> CheckpointSoundObject(TEXT("SoundCue'/Game/Hour_of_Code/Audio/SFX_checkpoint.SFX_checkpoint'"));
	if (CheckpointSoundObject.Succeeded())
	{
		CheckpointSound = CheckpointSoundObject.Object;

		CheckpointAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CheckpointAudioComponent"));
		CheckpointAudioComponent->SetupAttachment(RootComponent);

		CheckpointAudioComponent->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void ACheckpoint_HOC::BeginPlay()
{
	Super::BeginPlay();

	Button->SetMaterial(0, MaterialInstanceRef);

	if (CheckpointAudioComponent && CheckpointSound)
	{
		CheckpointAudioComponent->SetSound(CheckpointSound);
	}
}

// Called every frame
void ACheckpoint_HOC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint_HOC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (!CheckpointEnabled)
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));
			CheckpointEnabled = true;

			//Button->SetMaterial(0, MaterialInstanceRef);
			MaterialInstanceRef->SetVectorParameterValue(TEXT("Color"), FLinearColor::Blue);

			if (CheckpointAudioComponent && CheckpointSound)
			{
				CheckpointAudioComponent->Play(0.f);
			}
		}
	}
}
