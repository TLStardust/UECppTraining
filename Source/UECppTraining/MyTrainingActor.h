// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTrainingActor.generated.h"

UCLASS()
class UECPPTRAINING_API AMyTrainingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTrainingActor();
	UPROPERTY(EditDefaultsOnly,Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Stats")
	bool bIsInvincible = false;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void HealSelf(float Amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnHealthChanged(float NewHealth);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
