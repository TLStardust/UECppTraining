// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_AttackHitCheck.h"
#include "CombatInterface.h"

void UAN_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* Owner = MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("C++ Notify: Hit frame triggered on %s!"), *Owner->GetName());

		if (Owner->Implements<UCombatInterface>())
		{
			FDamageContext Context;
			Context.DamageAmount = 20.0f;
			ICombatInterface::Execute_OnTakeDamage(Owner, Context);
		}
	}
}