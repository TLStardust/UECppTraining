// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CppEventBus.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
/**
 * 
 */
UCLASS()
class UECPPTRAINING_API UCppEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// 暴露给蓝图，允许蓝图“赋值”和“绑定”
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	// 提供一个简单的函数供 C++ 或蓝图触发广播
	UFUNCTION(BlueprintCallable, Category = "Events")
	void BroadcastHealthChange(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "SafetyTest")
	void StartSafeTimer(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TriggerInterfaceTest(AActor* TargetActor);

	void OnTimerFinished(TWeakObjectPtr<AActor> WeakPtr);
};
