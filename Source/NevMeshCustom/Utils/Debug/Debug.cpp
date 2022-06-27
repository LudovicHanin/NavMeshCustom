// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug.h"

void UDebug::Log(const FString& _msg)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *_msg);
}

void UDebug::LogWarning(const FString& _msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *_msg);
}

void UDebug::LogError(const FString& _msg)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *_msg);
}
