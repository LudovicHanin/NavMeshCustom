// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Debug.generated.h"

/**
 * 
 */
UCLASS()
class NEVMESHCUSTOM_API UDebug : public UObject
{
	GENERATED_BODY()

public:
	static void Log(const FString& _msg);
	static void LogWarning(const FString& _msg);
	static void LogError(const FString& _msg);
};
