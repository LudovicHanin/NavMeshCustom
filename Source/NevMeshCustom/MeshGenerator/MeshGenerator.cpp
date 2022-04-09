#include "MeshGenerator.h"

#pragma region UnrealMethods
UMeshGenerator::UMeshGenerator()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMeshGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMeshGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
#pragma  endregion

#pragma region CustomMethods
#pragma region Private
#pragma endregion

#pragma region Public
#pragma endregion 
#pragma endregion 
