// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "TowerDefense/macros.h"
#include "EnemyBase.generated.h"

class ATrackLine;
class USplineComponent;
class UCapsuleComponent;

UCLASS()
class TOWERDEFENSE_API AEnemyBase : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Sets default values for this actor's properties
	AEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	float DefaultHealth;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Offset)
	float VerticalOffset = 0.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// VARIABLES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Component)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Component)
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Component)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Path)
	ATrackLine* TrackLine;

	USplineComponent* Path;

    FTimeline MoveTimeline;

	// FUNCTIONS
	UFUNCTION()
	virtual void MoveAlongTheLine(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES
	UPROPERTY(EditAnywhere, Category = Timeline)
    UCurveFloat* AlphaCurveFloat;

	UPROPERTY(EditAnywhere, Category = Timeline)
	float MovementSpeed;

	UFUNCTION()
	FVector GetLocationAfterTime(float Time);

	UFUNCTION(BlueprintCallable)
	void SetTrackLine(AActor* Track);

	UFUNCTION(BlueprintCallable)
	void SetAlphaCurve(UCurveFloat* Curve);

	UFUNCTION(BlueprintCallable)
	void StartRunning();

};
