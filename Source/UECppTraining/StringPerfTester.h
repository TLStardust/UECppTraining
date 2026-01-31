// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringPerfTester.generated.h"

/**
 * 
 */
UCLASS()
class UECPPTRAINING_API UStringPerfTester : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PerformanceTest")
	static void TestFStringAppend(int32 Iterations = 10000);

	UFUNCTION(BlueprintCallable, Category = "PerformanceTest")
	static void TestStringBuilderAppend(int32 Iterations = 10000);

};
