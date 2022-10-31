// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void CheckFireCondition();
	bool IsInFireScope() const;
	void HandleDestruction();

private:
	UPROPERTY()
		class ATank* Tank;
	UPROPERTY()
		FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere)
		float AttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
		float FireRate = 2.0f;
};
