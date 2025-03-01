// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.h"
#include "TowerBase.generated.h"

class USphereComponent;

UCLASS()
class TOWERDEFENSE_API ATowerBase : public AActor
{
	GENERATED_BODY()

	void FindTarget();

	UFUNCTION()
	void OnEnemyEnterShootRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEnemyOutOfShootRangeOrDied(AActor* OverlappedActor, AActor* OtherActor);
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shoot)
	AActor* ShootTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shoot)
	float ShootRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Shoot)
	USceneComponent* ShootLocation;

	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	TSubclassOf<class AEnemyBase> EnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shoot)
	bool bCanShoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shoot)
	float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shoot)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shoot)
	float DamageMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shoot)
	float HasteMultiplier = 1.f;

	FTimerHandle ShootTimeHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Component)
	UStaticMeshComponent* TowerBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Component)
	UStaticMeshComponent* TowerTop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Component)
	USphereComponent* ShootRange;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

	virtual void ShootHandle();

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
