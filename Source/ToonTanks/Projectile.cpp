// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = 1200.f;
	ProjectileMovementComponent->MaxSpeed = 1200.f;

	ProjectileTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	ProjectileTrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * @brief
 * @param HitComp 攻击组件
 * @param Actor 被攻击的对象
 * @param OtherComp 被击中组件
 * @param NormalImpulse
 * @param Hit
 */
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* Actor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const AActor* MyActor = GetOwner();
	if (MyActor == nullptr)
	{
		Destroy();
		return;
	}
	const auto OwnerInstigator = MyActor->GetInstigatorController();
	const auto DamageType = UDamageType::StaticClass();
	if (Actor && Actor != this && Actor != MyActor)
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), BaseDamage, OwnerInstigator, this, DamageType);
		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}
		if (HitSoundBase)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation(), GetActorRotation());
		}
		if (HitCameraShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
		}
	}
	Destroy();
}
