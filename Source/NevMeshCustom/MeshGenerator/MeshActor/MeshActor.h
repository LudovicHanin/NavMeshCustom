// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMeshInfo.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "MeshActor.generated.h"

struct FMyMeshInfo;
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

	UPROPERTY(VisibleAnywhere, Category	= "Mesh", meta = (DisplayName = "Mesh Info"))
	FMyMeshInfo mMeshInfo = FMyMeshInfo();
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
#pragma region Debug
	void DrawVerticesLocation();
#pragma endregion
#pragma endregion

#pragma region Public
public:
	void InitMesh(const TArray<FVector>& _vertices, const TArray<int32>& _triangles, const TArray<FVector2d> _uvs);
	void InitMesh(const FMyMeshInfo& _meshInfo);
#pragma endregion
#pragma endregion
};
