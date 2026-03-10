// Fill out your copyright notice in the Description page of Project Settings.


#include "APoolProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BattleManagerSubsystem.h"

// Sets default values
AAPoolProjectile::AAPoolProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 1. 初始化碰撞体
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAPoolProjectile::OnHit); // 绑定碰撞事件
	RootComponent = CollisionComp;

	// 2. 初始化飞行组件
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true; // 让它弹一下，方便观察
	ProjectileMovement->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AAPoolProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPoolProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPoolProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 关键逻辑：撞击后回收，而不是销毁
	GetWorldTimerManager().ClearTimer(LifeTimerHandle);
	if (UBattleManagerSubsystem* PoolSub = GetWorld()->GetSubsystem<UBattleManagerSubsystem>())
	{
		PoolSub->ReturnToPool(this);
	}
}

void AAPoolProjectile::ActivateProjectile(FVector Location, FRotator Rotation)
{
	SetActorLocationAndRotation(Location, Rotation);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	// 开启 5 秒计时器
	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &AAPoolProjectile::OnLifeExpired, 5.0f, false);

	// 重置速度
	ProjectileMovement->Velocity = Rotation.Vector() * ProjectileMovement->InitialSpeed;
	ProjectileMovement->Activate(true);
}

void AAPoolProjectile::OnLifeExpired()
{
	if (UBattleManagerSubsystem* PoolSub = GetWorld()->GetSubsystem<UBattleManagerSubsystem>())
	{
		PoolSub->ReturnToPool(this);
	}
}