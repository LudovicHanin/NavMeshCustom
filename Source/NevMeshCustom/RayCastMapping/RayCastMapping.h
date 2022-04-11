// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RayCastMapping.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEVMESHCUSTOM_API URayCastMapping : public UActorComponent
{
	GENERATED_BODY()

#pragma region Event
	DECLARE_EVENT_OneParam(URayCastMapping, FOnLaunchPointCalculate, const TArray<FVector>&)

	DECLARE_EVENT(URayCastMapping, FOnLaunchRayCast)

	DECLARE_DELEGATE_OneParam(FOnRayCastFinish, const TArray<FHitResult>&);

	FOnLaunchPointCalculate mOnLaunchPointCalculate;
	FOnLaunchRayCast mOnLaunchRayCast;
	FOnRayCastFinish mOnRayCastFinish;
#pragma endregion

#pragma region F/P
#pragma region Private
	UPROPERTY()
	UWorld* mWorld = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "RayCast", meta = (DisplayName = "RayCast Hits"))
	TArray<FHitResult> mAllHitResults = TArray<FHitResult>();

	UPROPERTY(VisibleAnywhere, Category = "RayCast", meta = (DisplayName = "RayCast Position"))
	TArray<FVector> mAllRayCastPosition = TArray<FVector>();

	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Collision Channel"))
	TEnumAsByte<ECollisionChannel> mCollisionChannel = ECC_WorldStatic;

	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Center Point"))
	FVector mLaunchPoint = FVector::ZeroVector;


	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Radius X"))
	float mRadiusX = 1;

	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Radius Y"))
	float mRadiusY = 1;

	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Radius Z"))
	float mRadiusZ = 1;

	UPROPERTY(EditAnywhere, Category = "RayCast",
		meta = (DisplayName = "Number Of Raycast", UIMin = "1", ClampMin = "1"))
	int mNumberOfRayCast = 1;

	UPROPERTY(VisibleAnywhere, Category = "RayCast", meta = (DisplayName = "Number of RayCast Per Line"))
	uint8 mNumberPerLine = 0;

	UPROPERTY(EditAnywhere, Category = "RayCast", meta = (DisplayName = "Launch RayCast"))
	bool mIsLaunchPointCalculated = false;

#pragma region Debug
	UPROPERTY(EditAnywhere, Category = "Debug", meta = (DisplayName = "Display Debug"))
	bool mDisplayDebug = true;
	UPROPERTY(EditAnywhere, Category = "Debug", meta = (DisplayName = "Display Radius"))
	bool mDisplayRadius = true;
	UPROPERTY(EditAnywhere, Category = "Debug", meta = (DisplayName = "Display RayCast Point"))
	bool mDisplayRayCastPoint = true;
#pragma endregion
#pragma endregion

#pragma region Public
#pragma endregion
#pragma endregion

#pragma region UnrealMethods
public:
	URayCastMapping();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region CustomMethods
#pragma region Private
	/**
	* @brief Init variable and calculate launch location of all RayCast/LineTrace
	*/
	void Init();

	/**
	 * @brief Add all methode to corresponding event
	 */
	void RegisterEvent();

	/**
	* @brief Calculate Launch location of all RayCast/LineTrace and stock them in mAllRayCastPosition
	*/
	void CalculateLaunchLocation();

	/**
	* @brief If all RayCast Launch Location as been calculated Launch RayCast/LineTrace
	*/
	void LaunchRayCast();

#pragma region Debug
	/**
	 * @brief Call all Debug Methods
	 */
	void DrawVisualDebug() const;

	/**
	* @brief Draw a Debug Box of the Radius of spawn of the RayCast/LineTrace
	*/
	void DrawRadiusDebug() const;

	/**
	* @brief Draw a Sphere at each launch position of RayCast/LineTrace
	*/
	void DrawRayCastPosition() const;
#pragma endregion
#pragma endregion

#pragma region Public
public:
	/**
	* @brief Start launching LineTrace from the top to the bottom to map and construct the NavMesh
	*/
	UFUNCTION()
	void StartRayCast();

#pragma region Getter
	FORCEINLINE FOnRayCastFinish& GetOnRayCastFinish() { return mOnRayCastFinish; }
	FORCEINLINE uint8& GetNumberPerLine() { return mNumberPerLine; }
#pragma endregion
#pragma endregion
#pragma endregion
};
