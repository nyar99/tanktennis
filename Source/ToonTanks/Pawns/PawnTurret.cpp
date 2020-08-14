// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GamePlayStatics.h"
#include "PawnTank.h"
#include "PawnTurret.h"


void APawnTurret::CheckFireCondition()
{
	if (!PlayerTank) {
		return;
	}

	if (ReturnDistanceToPlayer() < FireRange) {
		if (PlayerTank->getIsPlayerAlive()) {
			Fire();
		}
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerTank) {
		return 0.0f;
	}
	return FVector::Dist(PlayerTank ->GetActorLocation(), GetActorLocation());
}

APawnTurret::APawnTurret()
{
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank || ReturnDistanceToPlayer() > FireRange) {
		return;
	}
	
	FVector PlayerLocation = PlayerTank -> GetActorLocation();
	RotateTurret(PlayerLocation);
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
