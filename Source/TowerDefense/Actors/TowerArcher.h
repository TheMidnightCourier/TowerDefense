// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "ProjectileBase.h"
#include "TowerArcher.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerArcher : public ATowerBase
{
	GENERATED_BODY()
public:
	ATowerArcher();

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;
protected:
	void Shoot() override;
	void ShootHandle() override;
};
