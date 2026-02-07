// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleDataManager.generated.h"

USTRUCT(BlueprintType)
struct FMyUnitData
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	float Health;

	FMyUnitData():Position(FVector::ZeroVector),Health(100.0f){}
};

UCLASS()
class UECPPTRAINING_API ABattleDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleDataManager();

	UFUNCTION(BlueprintCallable, Category = "PerformanceTest")
	void RunPerformanceTest();

	UFUNCTION(BlueprintCallable, Category = "PerformanceTest")
	void RunReserveTest();

	UFUNCTION(BlueprintCallable, Category = "PerformanceTest")
	void RunRemoveTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 实验 A 的容器：存指针
	TArray<AActor*> ActorPointerArray;

	// 实验 B 的容器：存结构体数据
	TArray<FMyUnitData> StructDataArray;

	// 每一组测试的数量
	const int32 TestCount = 10000;
};

template<typename T>
void FastRemove(TArray<T>& Array, int32 Index)
{
	if (!Array.IsValidIndex(Index))
	{
		return;
	}

	if (Index == Array.Num())
	{
		Array.Pop();
		return;
	}

	Array[Index] = MoveTemp(Array[Array.Num() - 1]);
	Array.Pop();
}