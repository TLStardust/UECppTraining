// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!AIPawn || !PlayerPawn)
	{
		return;
	}
	float Dist = FVector::Dist(AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}
	BlackboardComp->SetValueAsFloat(DistanceKey.SelectedKeyName, Dist);
	float CheckValue = BlackboardComp->GetValueAsFloat(DistanceKey.SelectedKeyName);
	UE_LOG(LogTemp, Error, TEXT(">> DEBUG CHECK: Calculated: %f | Blackboard Has: %f"), Dist, CheckValue);
}