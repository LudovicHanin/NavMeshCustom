// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshInfo.generated.h"


USTRUCT()
struct FMeshInfo
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FVector> mVertices = TArray<FVector>();
	UPROPERTY()
	TArray<int32> mTriangles = TArray<int32>();
	UPROPERTY()
	TArray<FVector2D> mUVS = TArray<FVector2D>();

public:
#pragma region Constructor
	/**
	 * @brief Default constructor
	 */
	FMeshInfo()
	{
		mVertices = TArray<FVector>();
		mTriangles = TArray<int32>();
		mUVS = TArray<FVector2D>();
	}

	/**
	 * @brief Constructor that init all
	 * @param _vertices 
	 * @param _triangles 
	 * @param _uvs 
	 */
	FMeshInfo(const TArray<FVector>& _vertices, const TArray<int32>& _triangles, const TArray<FVector2D>& _uvs)
	{
		mVertices = _vertices;
		mTriangles = _triangles;
		mUVS = _uvs;
	}

	/**
	 * @brief Constructor by copy
	 * @param _meshInfo Copy of MeshInfo
	 */
	FMeshInfo(const FMeshInfo& _meshInfo)
	{
	}
#pragma endregion

#pragma region Getter
	FORCEINLINE TArray<FVector> GetVertices() const { return mVertices; }
	FORCEINLINE TArray<int32> GetTriangles() const { return mTriangles; }
	FORCEINLINE TArray<FVector2D> GetUVS() const { return mUVS; }
#pragma endregion
};
