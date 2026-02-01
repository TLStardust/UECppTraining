// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleDataManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleDataManager::ABattleDataManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleDataManager::BeginPlay()
{
	Super::BeginPlay();
	RunRemoveTest();
	RunReserveTest();
}

// Called every frame
void ABattleDataManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleDataManager::RunPerformanceTest()
{
	ActorPointerArray.Empty();
	StructDataArray.Empty();

	ActorPointerArray.Reserve(TestCount);
	StructDataArray.Reserve(TestCount);

	if (!GetWorld()) return;

	for (int32 i = 0; i < TestCount; i++)
	{
		// --- 修改点：明确指定使用 AActor 的 StaticClass ---
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// 使用最稳健的 Spawn 签名
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

		if (NewActor)
		{
			ActorPointerArray.Add(NewActor);
		}

		// B. 直接向结构体数组添加数据
		StructDataArray.Add(FMyUnitData());
	}

	UE_LOG(LogTemp, Warning, TEXT("=== 性能测试开始 (数量: %d) ==="), TestCount);
	double StartTimeA = FPlatformTime::Seconds();
	for (AActor* ActorPtr : ActorPointerArray)
	{
		if (ActorPtr)
		{
			// 模拟一个简单的数学运算：获取位置并加上一个偏移量
			FVector Loc = ActorPtr->GetActorLocation();
			Loc += FVector(1.0f, 1.0f, 1.0f);
			ActorPtr->SetActorLocation(Loc);
		}
	}

	double EndTimeA = FPlatformTime::Seconds();
	double TotalTimeA = (EndTimeA - StartTimeA) * 1000.0; // 转换为毫秒
	double StartTimeB = FPlatformTime::Seconds();

	for (FMyUnitData& Data : StructDataArray)
	{
		// 执行完全相同的数学运算
		Data.Position += FVector(1.0f, 1.0f, 1.0f);
		Data.Health -= 1.0f;
	}

	double EndTimeB = FPlatformTime::Seconds();
	double TotalTimeB = (EndTimeB - StartTimeB) * 1000.0; // 转换为毫秒

	// --- 结果打印 ---
	UE_LOG(LogTemp, Error, TEXT("实验 A (指针数组) 耗时: %f ms"), TotalTimeA);
	UE_LOG(LogTemp, Error, TEXT("实验 B (结构体数组) 耗时: %f ms"), TotalTimeB);
	UE_LOG(LogTemp, Warning, TEXT("DOD 速度是 OOP 的 %.2f 倍！"), TotalTimeA / TotalTimeB);

}

void ABattleDataManager::RunRemoveTest()
{
	const int32 ArraySize = 20000;
	const int32 RemoveCount = 10000;

	TArray<int32> ArrayA, ArrayB;
	for (int32 i = 0; i < ArraySize; i++)
	{
		ArrayA.Add(i);
		ArrayB.Add(i);
	}

	double StartTimeA = FPlatformTime::Seconds();
	while (ArrayA.Num() > 0) // 确保数组不为空
	{
		ArrayA.RemoveAt(ArrayA.Num() / 2);
	}
	double EndTimeA = FPlatformTime::Seconds();
	double StartTimeB = FPlatformTime::Seconds();
	for (int32 i = 0; i < RemoveCount; i++)
	{
		// 每次都删除中间元素，但使用 Swap 模式
		ArrayB.RemoveAtSwap(ArrayB.Num() / 2);
	}
	double EndTimeB = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Error, TEXT("删除测试 (1万次): RemoveAt耗时 %f ms, RemoveAtSwap耗时 %f ms"),
		(EndTimeA - StartTimeA) * 1000.f, (EndTimeB - StartTimeB) * 1000.f);
}

void ABattleDataManager::RunReserveTest()
{
	const int32 LargeTestCount = 100000; // 10万次操作
	TArray<int32> TestArray;

	// --- 实验 1：普通的 Add (不断扩容搬家) ---
	TestArray.Empty();
	double StartTime1 = FPlatformTime::Seconds();
	for (int32 i = 0; i < LargeTestCount; i++)
	{
		TestArray.Add(i);
	}
	double EndTime1 = FPlatformTime::Seconds();

	// --- 实验 2：Reserve 后的 Add (一次开好房，直接入住) ---
	TestArray.Empty();
	double StartTime2 = FPlatformTime::Seconds();

	TestArray.Reserve(LargeTestCount); // 关键动作：预留空间

	for (int32 i = 0; i < LargeTestCount; i++)
	{
		TestArray.Add(i);
	}
	double EndTime2 = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Warning, TEXT("Reserve 测试 (10万次): 普通Add耗时 %f ms, Reserve后Add耗时 %f ms"),
		(EndTime1 - StartTime1) * 1000.f, (EndTime2 - StartTime2) * 1000.f);
}
