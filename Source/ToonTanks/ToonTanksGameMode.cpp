// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowersCount = Towers.Num();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		//用于在游戏开始时延时DelayTime，FTimerDelegate委托的作用是当延时到了的时候调用绑定的
		//SetPlayerEnableState函数，并置为true，即游戏开始
		FTimerHandle PlayerEnableTimerHandle;
		const FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnableState,
			true
		);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			DelayTime,
			false
		);
	}
}

/**
 * @brief 用来对对象进行销毁调用
 * @param DeadActor 死亡对象
 */
void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
		GameEnd(false);
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
		DestoryedTowers += 1;
		if (TowersCount == DestoryedTowers)
			GameEnd(true);
	}
}

