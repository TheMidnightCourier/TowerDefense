// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackLine.h"
#include "Components/SplineComponent.h"

// Sets default values
ATrackLine::ATrackLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PathLine = CreateDefaultSubobject<USplineComponent>("Path Line");
}

// Called when the game starts or when spawned
void ATrackLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

