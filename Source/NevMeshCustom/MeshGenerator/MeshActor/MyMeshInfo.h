#pragma once

#include "CoreMinimal.h"
#include "MyMeshInfo.generated.h"

USTRUCT()
struct FMyMeshInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Vertices"))
	TArray<FVector> mVertices = TArray<FVector>();
	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Triangles"))
	TArray<int32> mTriangles = TArray<int32>();
	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "UV"))
	TArray<FVector2D> mUVS = TArray<FVector2D>();

public:
#pragma region Constructor
	/**
	 * @brief Default constructor
	 */
	FMyMeshInfo()
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
	FMyMeshInfo(const TArray<FVector>& _vertices, const TArray<int32>& _triangles, const TArray<FVector2D>& _uvs = TArray<FVector2D>())
	{
		mVertices = _vertices;
		mTriangles = _triangles;
		mUVS = _uvs;
	}

	/**
	 * @brief Constructor by copy
	 * @param _meshInfo Copy of MeshInfo
	 */
	FMyMeshInfo(const FMyMeshInfo& _meshInfo)
	{
		mVertices = _meshInfo.GetVertices();
		mTriangles = _meshInfo.GetTriangles();
		mUVS = _meshInfo.GetUVS();
	}
#pragma endregion

#pragma region Getter
	FORCEINLINE TArray<FVector> GetVertices() const { return mVertices; }
	FORCEINLINE TArray<int32> GetTriangles() const { return mTriangles; }
	FORCEINLINE TArray<FVector2D> GetUVS() const { return mUVS; }
#pragma endregion

#pragma region Setter
	FORCEINLINE void SetVertices(const TArray<FVector>& _vertices) { mVertices = _vertices; }
	FORCEINLINE void SetTriangles(const TArray<int32>& _triangles) { mTriangles = _triangles; }
	FORCEINLINE void SetUVS(const TArray<FVector2D>& _uvs) { mUVS = _uvs; }
#pragma endregion
};
