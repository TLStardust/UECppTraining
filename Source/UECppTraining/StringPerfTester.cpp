// Fill out your copyright notice in the Description page of Project Settings.


#include "StringPerfTester.h"
#include "HAL/PlatformTime.h"
#include "Misc/StringBuilder.h"

void UStringPerfTester::TestFStringAppend(int32 Iterations)
{
	FString FinalString = TEXT("");
	FString AppendContent = TEXT("Performance_Test_Data");
	double StartTime = FPlatformTime::Seconds();
	for (int32 i = 0; i <= Iterations; i++)
	{
		FinalString += AppendContent;
	}
	double EndTime = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT(" == = FString 测试结果 == = "));
	UE_LOG(LogTemp, Warning, TEXT("拼接次数: %d | 耗时: %f 秒"), Iterations, EndTime - StartTime);
}

void UStringPerfTester::TestStringBuilderAppend(int32 Iterations)
{
	// TStringBuilder<2048> 会在栈上预分配 2048 字节的空间
	// 只有超过这个大小时才会去堆上申请内存，极大地减少了内存分配次数
	TStringBuilder<2048> Builder;
	FString AppendContent = TEXT("Performance_Test_Data_");

	double StartTime = FPlatformTime::Seconds();

	for (int32 i = 0; i < Iterations; ++i)
	{
		Builder.Append(AppendContent);
	}

	// 最终可以转回 FString（如果需要）
	FString FinalString = Builder.ToString();

	double EndTime = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Warning, TEXT("=== TStringBuilder 测试结果 ==="));
	UE_LOG(LogTemp, Warning, TEXT("拼接次数: %d | 耗时: %f 秒"), Iterations, EndTime - StartTime);
}