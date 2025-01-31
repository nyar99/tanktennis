// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 1300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> HitShake;



	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalInpulse, const FHitResult& Hit);

	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
