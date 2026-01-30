// Fill out your copyright notice in the Description page of Project Settings.


#include "LifecycleReporterComponent.h"

// Sets default values for this component's properties
ULifecycleReporterComponent::ULifecycleReporterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void ULifecycleReporterComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT(">>> [Component] BeginPlay: 组件开始游戏逻辑 <<<"));
	// ...
	
}

void ULifecycleReporterComponent::OnRegister()
{
	Super::OnRegister();
	UE_LOG(LogTemp, Display, TEXT(">>> [Component] OnRegister: 组件已注册到世界 <<<"));
}

void ULifecycleReporterComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT(">>> [Component] InitializeComponent: 组件内部逻辑已就绪 <<<"));
}
// Called every frame
void ULifecycleReporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

