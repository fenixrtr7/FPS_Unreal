// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "FPS2\Damagable.h"
#include "FPS2\Pared.h"

void UShootComponent::Shoot(int amount, float shake)
{
	if (ammo > 0)
	{
		ammo--;

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
				GetComponentLocation(),
				GetComponentLocation() + GetForwardVector() * 10000 + shakeVector,
				ECC_GameTraceChannel3);

			DrawDebugLine(
				GetWorld(),
				GetComponentLocation(),
				GetComponentLocation() + GetForwardVector() * 10000 + shakeVector,
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
}
