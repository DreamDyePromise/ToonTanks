// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Mesh"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	Projectile = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	Projectile->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::TurretRotate(FVector TargetVec) const
{
	FVector LookAtVec = TargetVec - TurretMesh->GetComponentLocation();
	FRotator FinalRotate = FRotator(0.f, LookAtVec.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			FinalRotate,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			25.0f)
	);
}

void ABasePawn::Fire()
{
	auto ProjectileHelper = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Projectile->GetComponentLocation(), Projectile->GetComponentRotation());
	//�����ӵ��������ߣ��������ApplyDamage�����˺��¼���ʱ���ܹ����ɻ�ȡ�������ӵ�����
	ProjectileHelper->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	//������Ч
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	//������Ч
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	//����ͷ����
	if(DeathCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}
}
