// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS2_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) float life;
	UPROPERTY(EditAnywhere) float maxLife;
	UPROPERTY(EditAnywhere) TMap<FName, float> damages;

	void TakeDamage(float amount, FName boneName);
	void Heal(float amount);
};
