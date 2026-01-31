// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrainingActor.h"
#include"StringPerfTester.h"

// Sets default values
AMyTrainingActor::AMyTrainingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Display, TEXT("=== 构造函数已执行 ==="));
}

// Called when the game starts or when spawned
void AMyTrainingActor::BeginPlay()
{
	UE_LOG(LogTemp, Error, TEXT("=== [Actor] BeginPlay: Actor 觉醒，游戏正式开始！ ==="));
	Super::BeginPlay();
	UStringPerfTester::TestFStringAppend(1000000);
	UStringPerfTester::TestStringBuilderAppend(1000000);

}

// Called every frame
void AMyTrainingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTrainingActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("=== [Actor] PostInitializeComponents: 组件已全部初始化完毕 ==="));
}


void AMyTrainingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Display, TEXT("=== [Actor] OnConstruction: 构造脚本已执行 ==="));
}


void AMyTrainingActor::PostInitProperties()
{
	Super::PostInitProperties();
	UE_LOG(LogTemp, Warning, TEXT("=== [Actor] PostInitProperties: 属性已装填完毕 ==="));
}


void AMyTrainingActor::HealSelf(float Amount)
{
	MaxHealth += Amount;
	UE_LOG(LogTemp, Warning, TEXT("C++: HealSelf Called! Current Health: %f"), MaxHealth);
	OnHealthChanged(MaxHealth);
}