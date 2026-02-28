// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "CppEventBus.h"
#include "GameplayTagContainer.h"
#include "MyCharacter.generated.h"
class UHealthComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class UECPPTRAINING_API AMyCharacter : public ACharacter,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	FGameplayTagContainer ActiveGameplayTags;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	EActionState ActionState = EActionState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	void Input_Attack(const FInputActionValue& Value);

	virtual void OnTakeDamage_Implementation(const FDamageContext& Context) override;
};
