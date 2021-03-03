// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pared.generated.h"

UCLASS()
class FPS2_API APared : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float danoAAbsorver = 20;

};
