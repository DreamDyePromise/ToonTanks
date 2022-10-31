// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void HandleDestruction();
	APlayerController* GetTankController() const { return TankController; }

protected:
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	void Move(float Value);
	void Turn(float Value);
	bool IsAlive = true;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		FVector DeltaLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 500.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		FRotator DeltaRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RotateSpeed = 400.f;
	UPROPERTY(VisibleAnywhere)
		APlayerController* TankController;
};
