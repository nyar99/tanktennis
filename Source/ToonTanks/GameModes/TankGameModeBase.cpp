// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::HandleGameStart()
{
	GameStart();

	if (PlayerControllerRef) {
		PlayerControllerRef->SetPlayerEnabled(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabled, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameEnd(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	TargetTurrets = TurretActors.Num();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {
	if (DeadActor == PlayerTank) {
		PlayerTank->HandleDestruction();
		HandleGameEnd(false);
		if (PlayerControllerRef) {
			PlayerControllerRef->SetPlayerEnabled(false);
		}
		UE_LOG(LogTemp, Warning, TEXT("Player is supposed to lose"));
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
		DestroyedTurret->HandleDestruction();
		TargetTurrets -= 1;
		if (TargetTurrets == 0) {
			HandleGameEnd(true);
			UE_LOG(LogTemp, Warning, TEXT("Player is supposed to win"));
		}
	}
	
}
