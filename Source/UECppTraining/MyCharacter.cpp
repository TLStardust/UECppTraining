// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "HealthComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Input_Attack);
	}
}

void AMyCharacter::Input_Attack(const FInputActionValue& Value)
{
	if (ActionState != EActionState::Idle || !AttackMontage)
	{
		return;
	}
	ActionState = EActionState::Attacking;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(AttackMontage);
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AMyCharacter::OnAttackMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
	}
}

void AMyCharacter::OnTakeDamage_Implementation(const FDamageContext& Context)
{
	if (HealthComp)
	{
		HealthComp->DamageHealth(Context.DamageAmount);
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ActionState = EActionState::Idle;
}

void AMyCharacter::LoadSkillData(FName RowName)
{
	if (SkillTable)
	{
		// 这是 C++ 读取表的标准范式
		FSkillDataRow* Row = SkillTable->FindRow<FSkillDataRow>(RowName, TEXT("SkillSearchContext"));
		if (Row)
		{
			UE_LOG(LogTemp, Warning, TEXT("Data Found! Damage: %f"), Row->DamageMultiplier);
			// 此时你可以把这个数值赋值给你的战斗逻辑
		}
	}
}