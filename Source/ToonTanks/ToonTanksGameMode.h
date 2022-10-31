// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
		void GameEnd(bool IsWin);

public:
	void ActorDied(AActor* DeadActor);

private:
	void HandleGameStart();
	UPROPERTY()
		class ATank* Tank;
	UPROPERTY()
		class AToonTanksPlayerController* ToonTanksPlayerController;
	UPROPERTY(EditAnywhere)
		float DelayTime = 3.0f;
	UPROPERTY(VisibleAnywhere)
		int32 TowersCount = 0;
	UPROPERTY(VisibleAnywhere)
		int32 DestoryedTowers = 0;
};
