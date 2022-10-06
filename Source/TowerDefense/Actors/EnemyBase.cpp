// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "TrackLine.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
	CapsuleCollision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(CapsuleCollision);

	MovementSpeed = 300.f;

	DefaultHealth = 100.f;
	Health = DefaultHealth;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::OnDamageTaken);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeline.TickTimeline(DeltaTime);
}

void AEnemyBase::MoveAlongTheLine(float Value)
{
	float Distance = FMath::Lerp(VerticalOffset, Path->GetSplineLength(), Value);
	FVector LocationAlongSpline = Path->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World);
	//FVector NewLocation = LocationAlongSpline + FVector(0,0,0);
	FRotator RotationAlongSpline = Path->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World);

	SetActorLocationAndRotation(LocationAlongSpline, RotationAlongSpline);
	
}

FVector AEnemyBase::GetLocationAfterTime(float Time)
{
	float Seconds = Path->GetSplineLength()/MovementSpeed;
	DEBUGMESSAGE("Seconds played = %f", MoveTimeline.GetPlaybackPosition());
	float Distance = Time / Seconds * Path->GetSplineLength() + MoveTimeline.GetPlaybackPosition() * Seconds * MovementSpeed;
	return Path->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World);
}

void AEnemyBase::SetTrackLine(AActor* Track)
{
	ATrackLine* Line = Cast<ATrackLine>(Track);
	if (TrackLine || !Line) return;

	TrackLine = Line;
}

void AEnemyBase::SetAlphaCurve(UCurveFloat* Curve)
{
	if (AlphaCurveFloat) return;

	AlphaCurveFloat = Curve;
}

void AEnemyBase::StartRunning()
{
	if (AlphaCurveFloat && TrackLine)
    {
		Path = TrackLine->PathLine;
		float Seconds = Path->GetSplineLength()/MovementSpeed;
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Seconds to walk all path = %f"), Seconds));

        FOnTimelineFloat ProgressFunction;
        ProgressFunction.BindUFunction(this, FName("MoveAlongTheLine"));

        MoveTimeline.AddInterpFloat(AlphaCurveFloat, ProgressFunction);
		MoveTimeline.SetPlayRate(1.f/Seconds);
        MoveTimeline.PlayFromStart();
    }
}

void AEnemyBase::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0) return;

	Health -= Damage;
	DEBUGMESSAGE("Health left = %f", Health);

	if (FMath::IsNearlyZero(Health) || Health < 0)
	{
		this->Destroy();
	}
}
