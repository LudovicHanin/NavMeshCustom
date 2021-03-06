// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeshActor/MeshActor.h"
#include "MeshActor/MyMeshInfo.h"
#include "MeshGenerator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEVMESHCUSTOM_API UMeshGenerator : public UActorComponent
{
	GENERATED_BODY()

#pragma region Event
private:
	DECLARE_EVENT(UMeshGenerator, FOnMeshInfoCreate)

	DECLARE_EVENT(UMeshGenerator, FOnMeshCreate)

	FOnMeshInfoCreate mOnMeshInfoCreate;
	FOnMeshCreate mOnMeshCreate;
#pragma endregion

#pragma region F/P
#pragma region Private
private:
	UPROPERTY(EditAnywhere, Category = "Mesh | Actor", meta = (DisplayName = "Mesh Actor"))
	TSubclassOf<AMeshActor> mMeshActor = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Mesh | Actor", meta = (DisplayName = "All Mesh Actor"))
	TArray<AMeshActor*> mAllMeshActor = TArray<AMeshActor*>();

	UPROPERTY(VisibleAnywhere, Category = "Mesh | Info", meta = (DisplayName = "All mesh info"))
	TArray<FMyMeshInfo> mMeshInfos = TArray<FMyMeshInfo>();
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


#pragma endregion

#pragma region CustomMethods
#pragma region Private
private:
	/**
	* @brief Add all methode to corresponding event
	*/
	void RegisterEvent();

	/**
	 * @brief Make an array the will contains all vertex given
	 * @param _vertex1 Location of the first vertices
	 * @param _vertex2 Location of the second vertices
	 * @param _vertex3 Location of the third vertices
	 * @return An Array that contains the three vertex
	 */
	void CreateTriangle(const FVector& _vertex1, const FVector& _vertex2, const FVector& _vertex3);

	/**
	 * @brief Display mMesh
	 */
	UFUNCTION()
	void DisplayMesh();
#pragma endregion

#pragma region Public
public:
	/**
	* @brief Create a mesh
	* @param _vertices 
	* @param _triangles 
	* @param _uvs 
	*/
	UFUNCTION()
	void Init(const TArray<FHitResult>& _array, const int& _nbPerLine);

	/**
	* @brief Create recursively the Mesh of the NavMesh
	* @param _hitLocation Array that contains all location of the point touch by the RayCast/LineTrace
	* @param _index Current Index in the Array HitLocation
	* @param _nbPerLine Number of point per line
	*/
	UFUNCTION()
	void CreateMesh(const TArray<FVector> _hitLocation, const int _index, const int _nbPerLine);

	/**
	* @brief Make an array the will contains the UV
	* @param _uvX X value of the UV
	* @param _uvY Y value of the UV
	* @return An Array of UV
	*/
	static TArray<FVector2d> CreateUV(const float& _uvX, const float& _uvY);
#pragma endregion
#pragma endregion
};
