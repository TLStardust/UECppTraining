// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APoolProjectile.generated.h"

UCLASS()
class UECPPTRAINING_API AAPoolProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPoolProjectile();

	// 碰撞组件
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;

	// 飞行组件
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	// 撞击回调
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ActivateProjectile(FVector Location, FRotator Rotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FTimerHandle LifeTimerHandle;
	void OnLifeExpired(); // 5秒到期回调
};
