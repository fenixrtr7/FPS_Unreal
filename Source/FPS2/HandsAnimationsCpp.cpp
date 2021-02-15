// Fill out your copyright notice in the Description page of Project Settings.


#include "HandsAnimationsCpp.h"

void UHandsAnimationsCpp::NativeUpdateAnimation(float delta)
{
	speed = GetOwningActor()->GetVelocity().Size() / 2000;
}