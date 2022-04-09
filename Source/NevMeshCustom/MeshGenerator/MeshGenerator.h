// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "MeshGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEVMESHCUSTOM_API UMeshGenerator : public UActorComponent
{
	GENERATED_BODY()
	
	#pragma region Event
private:
	#pragma endregion
	
	#pragma region F/P
	#pragma region Private
private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (DisplayName = "Mesh"))
	UProceduralMeshComponent* mMesh = nullptr;
	#pragma endregion
	
	#pragma region Public
public:
	#pragma endregion
	#pragma endregion

    #pragma region UnrealMethods
public:	
	UMeshGenerator();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	#pragma endregion
	
	#pragma region CustomMethods
    #pragma region Private
private:
	static TArray<FVector>& CreateTriangle(const FVector& _vertex1, const FVector& _vertex2, const FVector& _vertex3);
    #pragma endregion
    	
    #pragma region Public
public:
    #pragma endregion
    #pragma endregion
};
