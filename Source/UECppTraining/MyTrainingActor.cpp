// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrainingActor.h"

// Sets default values
AMyTrainingActor::AMyTrainingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTrainingActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello Git and C++! The world begins here."));
	
}

// Called every frame
void AMyTrainingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTrainingActor::HealSelf(float Amount)
{
	MaxHealth += Amount;
	UE_LOG(LogTemp, Warning, TEXT("C++: HealSelf Called! Current Health: %f"), MaxHealth);
	OnHealthChanged(MaxHealth);
}