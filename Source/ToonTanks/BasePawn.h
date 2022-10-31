// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TurretRotate(FVector LocationVec) const;
	void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Projectile;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere)
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere)
		USoundBase* DeathSound;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeBase> DeathCameraShake;
	
};
