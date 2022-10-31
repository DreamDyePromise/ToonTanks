// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Tank) return;
	//每两秒钟调用一次
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsInFireScope()) TurretRotate(Tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
	if (IsInFireScope() && Tank->IsAlive) Fire();
}

bool ATower::IsInFireScope() const
{
	if (FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) <= AttackDistance) return true;
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
