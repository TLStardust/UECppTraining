// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_Player.h"
#include "Kismet/GameplayStatics.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is not vaild"));
		return;
	}

	AActor* TargetActor = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Second Time:EQS Context: CANNOT FIND PLAYER!"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Second Time:EQS Context: Found Player at %s"), *TargetActor->GetActorLocation().ToString());

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
}