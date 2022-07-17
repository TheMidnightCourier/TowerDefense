// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackLine.generated.h"

class USplineComponent;

UCLASS()
class TOWERDEFENSE_API ATrackLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackLine();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Path)
	USplineComponent* PathLine;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
