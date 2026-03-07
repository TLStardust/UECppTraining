// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class UECPPTRAINING_API UBTService_CheckDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Deltaseconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector DistanceKey;
};
