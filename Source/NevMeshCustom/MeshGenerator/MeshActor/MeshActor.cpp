// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshActor.h"

// Sets default values
AMeshActor::AMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	mMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeshActor::InitMesh(const TArray<FVector>& _vertices, const TArray<int32>& _triangles, const TArray<FVector2d> _uvs)
{
	if(!mMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("AMeshActor::InitMesh => No mesh"));
		return;
	}
	mMesh->CreateMeshSection_LinearColor(0, _vertices, _triangles, TArray<FVector>(), _uvs, TArray<FLinearColor>(),
										 TArray<FProcMeshTangent>(), true);
}

