// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

USTRUCT(BlueprintType)
struct FDamageContext
{
	GENERATED_BODY()

	// 伤害数值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageAmount = 0.0f;

	// 谁造成的伤害（伤害施加者）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	AActor* DamageCauser = nullptr;

	// 击中位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector HitLocation = FVector::ZeroVector;

	// 默认构造函数：确保变量在创建时有确定的初始值，防止随机数导致的 Bug
	FDamageContext()
	{
		// 可以在这里写初始化逻辑，也可以像上面那样直接在变量后面赋值
	}
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UECPPTRAINING_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnTakeDamage(const FDamageContext& Context);
};
