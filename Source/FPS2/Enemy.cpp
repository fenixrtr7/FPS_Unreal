// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Damage(float CurrentDamage, FName BoneName)
{
	if (damages.Contains(BoneName))
	{
		float damagePercentage = damages[BoneName];
		float totalDamage = CurrentDamage * damagePercentage;
		life -= totalDamage;

		/*UE_LOG(LogTemp, Warning, TEXT("Enemy life: %f"), life);
		UE_LOG(LogTemp, Warning, TEXT("Ejecutamos!!!!"));*/

		if (life <= 0)
		{
			Destroy();
		}
	}
}

void AEnemy::Cure(float amount)
{
	life += amount;

	if (life >= maxLife)
		life = maxLife;
}

