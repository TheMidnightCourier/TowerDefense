// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "ProjectileBomb.h"
#include "TowerBomber.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerBomber : public ATowerBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileBomb> ProjectileClass;
protected:
	void Shoot() override;
	void ShootHandle() override;
};
