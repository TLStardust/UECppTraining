// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BattleManagerSubsystem.generated.h"

/**
 * 
 */
USTRUCT()
struct FMonsterTickData 
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<AActor> ActorOwner;

	float CurrentHealth = 100.0f;
	float PoisonDamageRate = 5.0f;

	FMonsterTickData() {}
	FMonsterTickData(AActor* InOwner,float InHealth)
		:ActorOwner(InOwner),CurrentHealth(InHealth){ }
};

UCLASS()
class UECPPTRAINING_API UBattleManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void RegisterTickData(AActor* InOwner, float InHealth);

protected:
	void ProcessMassiveTick();

private:
	FTimerHandle GlobalTickHandle;

	UPROPERTY()
	TArray<FMonsterTickData> TickDataPool;
};
