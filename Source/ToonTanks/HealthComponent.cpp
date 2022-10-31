// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthValue = MaxHealthValue;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageHealth);

	MyGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
 * @brief
 * @param DamageActor �ܻ�����
 * @param Damage �˺�
 * @param Type
 * @param Player
 * @param DamageCauser �ӵ�
 */
void UHealthComponent::DamageHealth(AActor* DamageActor, float Damage, const UDamageType* Type, AController* Player, AActor* DamageCauser)
{
	if (Damage <= 0) return;
	HealthValue -= Damage;
	if (HealthValue <= 0 && MyGameMode) MyGameMode->ActorDied(DamageActor);
}

