// Fill out your copyright notice in the Description page of Project Settings.


#include "EpicCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEpicCharacter::AEpicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AEpicCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		OnTakeAnyDamage.AddDynamic(this, &AEpicCharacter::TakeDamage);
	}
}

// Called to bind functionality to input
void AEpicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AEpicCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEpicCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AEpicCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AEpicCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEpicCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEpicCharacter::StopJump);

	// Set up "sprint" bindings.
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEpicCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEpicCharacter::StopSprint);
}

void AEpicCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AEpicCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AEpicCharacter::StartJump()
{
	bPressedJump = true;
}

void AEpicCharacter::StopJump()
{
	bPressedJump = false;
}

void AEpicCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}

void AEpicCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AEpicCharacter::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	PlayerHealth = FMath::Clamp(PlayerHealth - Damage, 0.0f, 1.0f);

	if (PlayerHealth <= 0)
	{
		Destroy();
	}
}