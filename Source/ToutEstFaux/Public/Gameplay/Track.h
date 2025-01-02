// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Track.generated.h"

class USplineMeshComponent;

UCLASS()
class TOUTESTFAUX_API ATrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USplineComponent* Spline;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category=Spline)
	USplineComponent* GetSpline();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	USplineMeshComponent* GetNewMesh();

private:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UStaticMesh* TrackMesh=nullptr;

	UFUNCTION(BlueprintCallable)
	void SetUpMesh();
	
	UFUNCTION(BlueprintCallable)
	float GetXSize();

	UFUNCTION(BlueprintCallable)
	int GetMaxIndex();
	
	
};
