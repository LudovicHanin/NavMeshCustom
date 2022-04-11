#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NevMeshCustom/MeshGenerator/MeshGenerator.h"
#include "NevMeshCustom/RayCastMapping/RayCastMapping.h"
#include "NavMeshActor.generated.h"

UCLASS()
class NEVMESHCUSTOM_API ANavMeshActor : public AActor
{
	GENERATED_BODY()

#pragma region Event
private:
	DECLARE_EVENT(ANavMeshActor, FOnRayCastDown)

	FOnRayCastDown mOnRayCastDown;

	DECLARE_EVENT(ANavMeshActor, FOnMappingStart)

	FOnMappingStart mOnMappingStart;

	DECLARE_EVENT(ANavMeshActor, FOnMappingEnd)

	FOnMappingEnd mOnMappingEnd;
#pragma endregion

#pragma region F/P
#pragma region Private
private:
	UPROPERTY(VisibleAnywhere, Category = "Component | RayCast Mapping", meta = (DisplayName = "RayCast Mapping"))
	URayCastMapping* mRayCastMapping = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component | Mesh | Generate", meta =	(DisplayName = "Mesh Generator"))
	UMeshGenerator* mMeshGenerator = nullptr;
#pragma endregion

#pragma region Public
public:
#pragma endregion
#pragma endregion

public:
	ANavMeshActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region CustomMethods
#pragma region Private
#pragma endregion

#pragma region Public
void StartRayCast();
#pragma endregion 
#pragma endregion
};