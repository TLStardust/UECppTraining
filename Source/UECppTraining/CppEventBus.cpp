// Fill out your copyright notice in the Description page of Project Settings.


#include"CppEventBus.h"
#include"TimerManager.h"
#include"CombatInterface.h"

void UCppEventBus::BroadcastHealthChange(float NewValue)
{

}

void UCppEventBus::StartSafeTimer(AActor* TargetActor)
{
	if (!TargetActor)
	{
		return;
	}

	TWeakObjectPtr<AActor> WeakTarget = TargetActor;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, WeakTarget]()
		{
			if (WeakTarget.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Object [%s] of class [%s] is alive!"),
					*WeakTarget->GetName(),
					*WeakTarget->GetClass()->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Timer Safe: Actor was destroyed, but we avoided a CRASH!"));
			}
		}, 3.0f, false);
}

void UCppEventBus::TriggerInterfaceTest(AActor* TargetActor)
{
	if (!TargetActor)
	{
		return;
	}

	if (TargetActor->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_OnTakeDamage(TargetActor, 20.0f);
		UE_LOG(LogTemp, Warning, TEXT("Interface Bus: Sent Damage Command to %s"), *TargetActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interface Bus: Target does NOT have CombatInterface!"));
	}
}

void UCppEventBus::HandleStateChange(EActionState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
	case EActionState::Idle:
		UE_LOG(LogTemp, Log, TEXT("State: 角色回到闲置状态"));
		break;

	case EActionState::Attacking:
		UE_LOG(LogTemp, Warning, TEXT("State: 正在进入攻击态，禁止移动！"));
		break;

	case EActionState::Stunned:
		UE_LOG(LogTemp, Error, TEXT("State: 角色进入硬直，中断当前动作！"));
		break;

	case EActionState::Dead:
		UE_LOG(LogTemp, Fatal, TEXT("State: 角色死亡！游戏结束逻辑启动"));
		break;
	}
}