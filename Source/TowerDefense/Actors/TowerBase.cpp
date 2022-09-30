// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "Components/SphereComponent.h"
#include "TowerDefense/macros.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShootRange = CreateDefaultSubobject<USphereComponent>("Shoot Range");
	ShootRange->SetupAttachment(RootComponent);
	ShootRange->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnEnemyEnterShootRange);
	OnActorEndOverlap.AddDynamic(this, &ATowerBase::OnEnemyOutOfShootRangeOrDied);

	TowerBase = CreateDefaultSubobject<UStaticMeshComponent>("Tower Base");
	TowerBase->SetupAttachment(ShootRange);
	TowerBase->SetGenerateOverlapEvents(false);

	TowerTop = CreateDefaultSubobject<UStaticMeshComponent>("Tower Top");
	TowerTop->SetupAttachment(TowerBase);
	TowerTop->SetGenerateOverlapEvents(false);
	
	ShootRate = 1.f;
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATowerBase::Shoot(AActor* NewTarget)
{
	D("Shoot!");
	GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerBase::ShootHandle, ShootRate, true);
}

void ATowerBase::ShootHandle()
{
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(TowerTop->GetComponentLocation(), ShootTarget->GetActorLocation());
	NewRotation = FRotator(0, NewRotation.Yaw, 0);
	TowerTop->SetWorldRotation(NewRotation);
}

void ATowerBase::FindTarget()
{
	GetWorldTimerManager().ClearTimer(ShootTimeHandle);
	TArray<AActor*> TargetsInRange;
	ShootRange->GetOverlappingActors(TargetsInRange);
	if (!TargetsInRange.IsEmpty())
	{
		 ShootTarget = TargetsInRange[0];
		 Shoot(ShootTarget);
		 DEBUGMESSAGE("%s - Shoot Target", *(ShootTarget->GetName()));
	}
	else D("There is no enemy in shoot range");
}

void ATowerBase::OnEnemyEnterShootRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DEBUGMESSAGE("%s - in shoot range", *(OtherActor->GetName()));
	if(!ShootTarget) FindTarget();
}

void ATowerBase::OnEnemyOutOfShootRangeOrDied(AActor* OverlappedActor, AActor* OtherActor)
{
	DEBUGMESSAGE("%s - is out of range or died", *(OtherActor->GetName()));
	if(ShootTarget == OtherActor) FindTarget();
}