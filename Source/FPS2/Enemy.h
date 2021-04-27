// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damagable.h"
#include "Curable.h"
#include "MyInterface/PatrolObject.h"
#include "Enemy.generated.h"


UCLASS()
class FPS2_API AEnemy : public ACharacter, public IDamagable, public ICurable, public IPatrolObject
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class ULifeComponent* life;
	UPROPERTY(EditAnywhere) TArray<class ATargetPoint*> waypoints;

	void Damage(float amount, FName boneName) override;
	void Cure(float amount) override;
	TArray<class ATargetPoint*> GetWaypoints() override;
};
