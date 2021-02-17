// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnerCpp.h"
#include "Engine/World.h"

// Sets default values
AEnemySpawnerCpp::AEnemySpawnerCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnerCpp::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Random Place
	/*int spawnIndex = FMath::RandRange(0, spawnPoints.Num() - 1);
	AActor* spawnPoint = spawnPoints[spawnIndex];
	
	GetWorld()->SpawnActor<AActor>(blueprintToSpawn.Get(), spawnPoint->GetTransform());*/

	for (int i = 0; i < amount; i++)
	{
		int spawnPointIndex = FMath::RandRange(0, spawnPoints.Num() - 1);
		int blueprintIndex = FMath::RandRange(0, blueprintsToSpawn.Num() - 1);

		if (spawnPointIndex >= spawnPoints.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay spawn points en el spawner"));
			return;
		}
		
		if (blueprintIndex >= blueprintsToSpawn.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay bluePrint en el array"));
			return;
		}

		AActor* spawnPoint = spawnPoints[spawnPointIndex];
		TSubclassOf<AActor> blueprintToSpawn = blueprintsToSpawn[blueprintIndex];
		GetWorld()->SpawnActor<AActor>(blueprintToSpawn.Get(), spawnPoint->GetTransform());
	}
}

// Called every frame
void AEnemySpawnerCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

