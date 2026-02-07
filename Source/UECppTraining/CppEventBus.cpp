// Fill out your copyright notice in the Description page of Project Settings.


#include "CppEventBus.h"

void UCppEventBus::BroadcastHealthChange(float NewValue)
{
	// 触发广播，所有在这个事件上连了线的蓝图都会收到通知
	OnHealthChanged.Broadcast(NewValue);
}