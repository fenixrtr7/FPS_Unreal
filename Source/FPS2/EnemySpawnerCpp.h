// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnerCpp.generated.h"

UCLASS()
class FPS2_API AEnemySpawnerCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnerCpp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere) TArray<AActor*> spawnPoints;

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AActor>> blueprintsToSpawn;

	UPROPERTY(EditAnywhere) int amount = 1;

};
