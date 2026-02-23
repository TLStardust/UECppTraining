// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CppEventBus.generated.h"
UENUM(BlueprintType)
enum class EActionState :uint8
{
	Idle		UMETA(DisplayName = "闲置"),
	Attacking	UMETA(DisplayName = "攻击中"),
	Stunned		UMETA(DisplayName = "硬直/受击"),
	Dead		UMETA(DisplayName = "死亡")
};
/**
 * 
 */
UCLASS()
class UECPPTRAINING_API UCppEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// 暴露给蓝图，允许蓝图“赋值”和“绑定”

	// 提供一个简单的函数供 C++ 或蓝图触发广播
	UFUNCTION(BlueprintCallable, Category = "Events")
	void BroadcastHealthChange(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "SafetyTest")
	void StartSafeTimer(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TriggerInterfaceTest(AActor* TargetActor);

	void OnTimerFinished(TWeakObjectPtr<AActor> WeakPtr);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EActionState CurrentState = EActionState::Idle;

	UFUNCTION(BlueprintCallable, Category = "State")
	void HandleStateChange(EActionState NewState);
};
