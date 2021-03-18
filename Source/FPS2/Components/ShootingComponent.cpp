// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPS2\Damagable.h"
#include "FPS2\Pared.h"

// Sets default values for this component's properties

void UShootingComponent::Shooting(int amount, float shake, UCameraComponent *cam)
{
	if (CurrentBullets > 0)
	{
		CurrentBullets--;

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
}
