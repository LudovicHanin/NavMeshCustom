// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "MeshActor.generated.h"

UCLASS()
class NEVMESHCUSTOM_API AMeshActor : public AActor
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
	AMeshActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	#pragma endregion
	
	#pragma region CustomMethods
	#pragma region Private
private:
	#pragma endregion
	
	#pragma region Public
public:
	void InitMesh(const TArray<FVector>& _vertices, const TArray<int32>& _triangles, const TArray<FVector2d> _uvs);
	#pragma endregion
	#pragma endregion
};