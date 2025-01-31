// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabled(bool SetPlayerEnable) {
	if (SetPlayerEnable) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = !SetPlayerEnable;
}