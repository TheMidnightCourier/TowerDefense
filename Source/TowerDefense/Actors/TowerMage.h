// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "TowerMage.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerMage : public ATowerBase
{
	GENERATED_BODY()
protected:
	void Shoot() override;
	void ShootHandle() override;
};
