// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "EnemyBase.generated.h"

class ATrackLine;
class USplineComponent;
class UCapsuleComponent;

UCLASS()
class TOWERDEFENSE_API AEnemyBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// VARIABLES
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

};
