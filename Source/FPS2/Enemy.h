// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damagable.h"
#include "Curable.h"
#include "Enemy.generated.h"


UCLASS()
class FPS2_API AEnemy : public ACharacter, public IDamagable, public ICurable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere) float life = 100;
	UPROPERTY(EditAnywhere) float maxLife = 100;

	UPROPERTY(EditAnywhere) TMap<FName, float> damages;

	void Damage(float CurrentDamage, FName BoneName) override;
	void Cure(float amount) override;
};
