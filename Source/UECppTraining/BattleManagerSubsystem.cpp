// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSubsystem.h"

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