// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{	
	Super::HandleDestruction();
	IsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool APawnTank::getIsPlayerAlive()
{
	return IsPlayerAlive;
}

void APawnTank::CalculateMoveInput(float value)
{
	MoveDirection = FVector(value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}
 
void APawnTank::CalculateRotateInput(float value)
{
	float RotationAmount = value * TurnSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.f, RotationAmount, 0.f);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	Rotate();
	
	if (PlayerController) {
		FHitResult TraceHitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		FString HitLocationString = HitLocation.ToString();
		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}