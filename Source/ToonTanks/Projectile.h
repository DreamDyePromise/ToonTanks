// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovementComponent;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* Actor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
		float BaseDamage = 10.f;
	UPROPERTY(EditAnywhere)
		UParticleSystem* HitParticle;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ProjectileTrailParticle;
	UPROPERTY(EditAnywhere)
		USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere)
		USoundBase* HitSoundBase;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeBase> HitCameraShake;
};
