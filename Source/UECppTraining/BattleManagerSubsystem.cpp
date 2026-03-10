// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSubsystem.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UBattleManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GetWorld()->GetTimerManager().SetTimer(GlobalTickHandle, this, &UBattleManagerSubsystem::ProcessMassiveTick, 0.1f, true);
}

void UBattleManagerSubsystem::ProcessMassiveTick()
{
	float DeltaTime = 0.1f;
	for (int32 i = TickDataPool.Num() - 1; i >= 0; i--)
	{
		FMonsterTickData& Data = TickDataPool[i];

		if (Data.ActorOwner.IsValid())
		{
			Data.CurrentHealth = FMath::Max(Data.CurrentHealth - Data.PoisonDamageRate * DeltaTime, 0);
			if (FMath::IsNearlyZero(Data.CurrentHealth))
			{
				TickDataPool.RemoveAtSwap(i);
			}
		}
		else
		{
			TickDataPool.RemoveAtSwap(i);
		}
	}
}

void UBattleManagerSubsystem::RegisterTickData(AActor* InOwner, float InHealth)
{
	if (!InOwner)return;

	FMonsterTickData NewData;
	NewData.ActorOwner = InOwner;
	NewData.CurrentHealth = InHealth;
	NewData.PoisonDamageRate = 10.0f; 

	TickDataPool.Add(NewData);

	UE_LOG(LogTemp, Log, TEXT("成功注册敌人 Tick 数据: %s"), *InOwner->GetName());
}

AActor* UBattleManagerSubsystem::GetProjectile(TSubclassOf<AActor> ProjectileClass, FVector Location, FRotator Rotation)
{
	AAPoolProjectile* Proj = nullptr;

	// 1. 先尝试从池子里拿
	if (InactiveProjectilesPool.Num() > 0)
	{
		Proj = Cast<AAPoolProjectile>(InactiveProjectilesPool.Pop());
	}
	// 2. 如果池子空了，检查总数是否达到 20
	else
	{
		int32 TotalCount = ActiveProjectilesPool.Num() + InactiveProjectilesPool.Num();
		if (TotalCount < 20)
		{
			FActorSpawnParameters SpawnParams;
			Proj = GetWorld()->SpawnActor<AAPoolProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
		}
		else
		{
			// 这里可以选择：A.不发射；B.强制回收最老的一颗。这里先选 A。
			UE_LOG(LogTemp, Warning, TEXT("达到 20 发上限，拒绝发射！"));
			return nullptr;
		}
	}

	if (Proj)
	{
		ActiveProjectilesPool.Add(Proj);
		Proj->ActivateProjectile(Location, Rotation); // 调用我们刚才写的激活函数
	}

	return Proj;
}

void UBattleManagerSubsystem::ReturnToPool(AActor* Proj) 
{
	if (!Proj)return;
	ActiveProjectilesPool.RemoveSingleSwap(Proj);

	Proj->SetActorHiddenInGame(true);
	Proj->SetActorEnableCollision(false);

	if (UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Proj->GetRootComponent()))
	{
		RootComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
	}
	InactiveProjectilesPool.Push(Proj);
}