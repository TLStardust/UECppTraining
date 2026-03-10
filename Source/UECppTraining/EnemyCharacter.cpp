// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		MeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UBattleManagerSubsystem* BattleSub = GetWorld()->GetSubsystem<UBattleManagerSubsystem>())
	{
		BattleSub->RegisterTickData(this, 100.0f);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::PerformAttack()
{
	if (bIsAttacking || !AttackMontage)
	{
		return;
	}
	
	bIsAttacking = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(AttackMontage);
		FOnMontageEnded	EndDelegate;
		EndDelegate.BindUObject(this,&AEnemyCharacter::OnAttackedMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);

		UE_LOG(LogTemp, Warning, TEXT("Enemy Body: Swinging weapon!"));
	}
}

void AEnemyCharacter::OnAttackedMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
	UE_LOG(LogTemp, Warning, TEXT("Enemy Body: Attack finished. Ready for next command."));
}