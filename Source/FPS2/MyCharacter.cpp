// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Damagable.h"
#include "Pared.h"
#include "LifeComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	life = CreateDefaultSubobject<ULifeComponent>("Life Component");

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartShoot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopShoot);

	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &AMyCharacter::StartShoot2);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &AMyCharacter::StopShoot2);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shooting!"));

	GetWorldTimerManager().SetTimer(timerShootHandle, this, &AMyCharacter::ShootTimer, 0.267f, true);
}

void AMyCharacter::ShootTimer()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	//FHitResult hitInfo;
	//bool hasHit = GetWorld()->LineTraceSingleByChannel(
	//hitInfo,
	//cam->GetComponentLocation(),
	//cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
	//ECC_GameTraceChannel3);
	//if (hasHit && hitInfo.GetActor())
	//{
	//	//hitInfo.GetActor()->Destroy();
	//	//UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString());
	//	AEnemy* enemy = Cast<AEnemy>(hitInfo.GetActor());
	//	if (enemy && damages.Contains(hitInfo.BoneName))
	//	{
	//		float damagePercentage = damages[hitInfo.BoneName];
	//		float totalDamage = damage * damagePercentage;
	//		enemy->life -= totalDamage;
	//		UE_LOG(LogTemp, Warning, TEXT("Enemy life: %f"), enemy->life);
	//	}
	//}

	Shoot(1, 0);
}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(timerShootHandle);
}

void AMyCharacter::StartShoot2()
{
	GetWorldTimerManager().SetTimer(timerShootHandle2, this, &AMyCharacter::ShootTimer2, 0.267f, true);
}

void AMyCharacter::ShootTimer2()
{
	//Shoot(10, 1000);
	Heal();
}

void AMyCharacter::StopShoot2()
{
	GetWorldTimerManager().ClearTimer(timerShootHandle2);
}

void AMyCharacter::Shoot(int amount, float shake)
{
	for (int j = 0; j < amount; j++)
	{
		TArray<FHitResult> hits;
		float currentDamage = damage;

		FVector shakeVector;
		shakeVector.X = FMath::RandRange(-shake, shake);
		shakeVector.Y = FMath::RandRange(-shake, shake);
		shakeVector.Z = FMath::RandRange(-shake, shake);

		GetWorld()->LineTraceMultiByChannel(
			hits,
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000 + shakeVector,
			ECC_GameTraceChannel3);

		DrawDebugLine(
			GetWorld(),
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000 + shakeVector,
			FColor::Red,
			false,
			3);

		TArray<AActor*> hittedActors;

		for (int i = 0; i < hits.Num(); i++)
		{
			FHitResult hitInfo = hits[i];

			if (hitInfo.GetActor() && !hittedActors.Contains(hitInfo.GetActor()))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString());

				hittedActors.Add(hitInfo.GetActor());
				UE_LOG(LogTemp, Warning, TEXT("Damage Hit"));

				IDamagable* damagable = Cast<IDamagable>(hitInfo.GetActor());
				if (damagable)
				{
					damagable->Damage(currentDamage, hitInfo.BoneName);
					//UE_LOG(LogTemp, Warning, TEXT("Current Damage: %s"), *currentDamage);
				}

				APared* pared = Cast<APared>(hitInfo.GetActor());
				if (pared) // = (Pared != nullptr) 
				{
					currentDamage -= pared->danoAAbsorver;
				}
			}
		}
	}
}

void AMyCharacter::Heal()
{
	FHitResult hitInfo;
	GetWorld()->LineTraceSingleByChannel(
		hitInfo,
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 10000,
		ECC_GameTraceChannel3);

	DrawDebugLine(
		GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 10000,
		FColor::Green,
		false,
		3);

		if (hitInfo.GetActor())
		{
			//UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString());

			UE_LOG(LogTemp, Warning, TEXT("Heal hit"));

			ICurable* curable = Cast<ICurable>(hitInfo.GetActor());
			if (curable)
			{
				curable->Cure(healAmount);
				//UE_LOG(LogTemp, Warning, TEXT("Current Damage: %s"), *currentDamage);
			}
		}
	
	
}

