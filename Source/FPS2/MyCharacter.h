// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FPS2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere) float rotationSpeed = 45;
	UPROPERTY(EditAnywhere) float damage = 100;
	UPROPERTY(EditAnywhere) float healAmount = 50;

	// Add CAM
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class ULifeComponent* life;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UCameraComponent* cam;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* arms;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* weapon;

	FTimerHandle timerShootHandle;
	FTimerHandle timerShootHandle2;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void RotateYaw(float value);
	void RotatePitch(float value);

	void StartJump();
	void StopJump();

	void StartShoot();
	void ShootTimer();
	void StopShoot();

	void StartShoot2();
	void ShootTimer2();
	void StopShoot2();

	void Shoot(int amount, float shake);
	void Heal();
};
