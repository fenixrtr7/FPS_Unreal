// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add Cam
	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->bUsePawnControlRotation = true;
	cam->SetupAttachment(GetRootComponent());

	// Add arms
	arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	arms->bCastStaticShadow = false;
	arms->SetupAttachment(cam);

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->bCastStaticShadow = false;
	weapon->SetupAttachment(arms, "GripPoint");
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Begin!"));
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::RotatePitch);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMyCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Shooting);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopShoot);
}

void AMyCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::RotateYaw(float value)
{
	AddControllerYawInput(value * rotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::RotatePitch(float value)
{
	AddControllerPitchInput(value * rotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::StartJump()
{
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::StartShoot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	FHitResult hitInfo;
	bool hasHit = GetWorld()->LineTraceSingleByChannel(
		hitInfo,
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
		ECC_GameTraceChannel3);

	DrawDebugLine(
		GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
		FColor::Red,
		false,
		3);

	if (hasHit && hitInfo.GetActor())
	{
		//hitInfo.GetActor()->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString());
	}
}

void AMyCharacter::Shooting()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shooting!"));

	GetWorldTimerManager().SetTimer(timerShootHandle, this, &AMyCharacter::StartShoot, 0.267f, true);
}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(timerShootHandle);
}

