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

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Shoot)
	bool HasFireDamage;
protected:
	void Shoot() override;
	void ShootHandle() override;
};
