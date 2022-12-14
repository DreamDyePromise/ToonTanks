// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	class AToonTanksGameMode* MyGameMode;

private:
	UPROPERTY(EditAnywhere)
		float MaxHealthValue = 100.f;
	UPROPERTY(VisibleAnywhere)
		float HealthValue = 0.f;
	UFUNCTION()
		void DamageHealth(AActor* DamageActor, float Damage, const UDamageType* Type, AController* Player, AActor* DamageCauser);
};
