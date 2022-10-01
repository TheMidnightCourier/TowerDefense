// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBomb.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AProjectileBomb : public AProjectileBase
{
	GENERATED_BODY()
public:
	AProjectileBomb();

	void SetInitialSpeedByTargetDistance(FVector Location, float ShootRate);
};
