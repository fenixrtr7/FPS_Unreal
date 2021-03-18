// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS2_API UShootComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere) int ammo = 10;
	UPROPERTY(EditAnywhere) int damage = 10;

	UPROPERTY(EditAnywhere) TSubclassOf<class AActor> bulletBlueprint;

	void Shoot(int amount, float shake);

		
};
