// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "EnemyCharacter.h"

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_AttackPlayer: Failed - AIController is NULL!"));
		return EBTNodeResult::Failed;
	}
	
	AEnemyCharacter* MyEnemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!MyEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTTask_AttackPlayer: Failed - EnemyCharacter Pawn not found!"));
		return EBTNodeResult::Failed;
	}

	MyEnemy->PerformAttack();

	UE_LOG(LogTemp, Log, TEXT("BTTask_AttackPlayer: Success - Attack command issued to %s"), *MyEnemy->GetName());

	return EBTNodeResult::Succeeded;
}