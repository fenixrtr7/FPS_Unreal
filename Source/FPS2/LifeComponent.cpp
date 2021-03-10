// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "GameFramework\Actor.h"

void ULifeComponent::TakeDamage(float amount, FName boneName)
{
	if (damages.Contains(boneName))
	{
		float damagePercentage = damages[boneName];
		float totalDamage = amount * damagePercentage;
		life -= totalDamage;

		/*UE_LOG(LogTemp, Warning, TEXT("Enemy life: %f"), life);
		UE_LOG(LogTemp, Warning, TEXT("Ejecutamos!!!!"));*/

		if (life <= 0)
		{
			GetOwner()->Destroy();
		}
	}
}

void ULifeComponent::Heal(float amount)
{
	life += amount;

	if (life >= maxLife)
		life = maxLife;
}
