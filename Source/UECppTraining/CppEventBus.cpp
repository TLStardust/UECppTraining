// Fill out your copyright notice in the Description page of Project Settings.


#include"TimerManager.h"
#include"CombatInterface.h"
#include "CppEventBus.h"

void UCppEventBus::BroadcastHealthChange(float NewValue)
{
	// 触发广播，所有在这个事件上连了线的蓝图都会收到通知
	OnHealthChanged.Broadcast(NewValue);
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