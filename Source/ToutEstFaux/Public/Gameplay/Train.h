// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "GameFramework/Pawn.h"
#include "Train.generated.h"

UCLASS()
class TOUTESTFAUX_API ATrain : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Locomotive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere,Category="Track",meta=(AllowPrivateAccess))
	ATrack* MyTrack =nullptr;
	
	UPROPERTY(BlueprintReadWrite,Category="Initiation",meta=(AllowPrivateAccess))
	TArray <UStaticMeshComponent*> Wagons {};

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Initiation",meta=(AllowPrivateAccess))
	int NumberOfWagon = 0;

	UPROPERTY(EditAnywhere,Category="Initiation",meta=(AllowPrivateAccess))
	float Speed = 100.f;

	uint8 ColorIndex=0;

	UPROPERTY(EditDefaultsOnly,Category="Initiation",meta=(AllowPrivateAccess))
	float WagonSize = 30.f;

	UPROPERTY(EditDefaultsOnly,Category="Initiation",meta=(AllowPrivateAccess))
	TArray<UMaterialInstance*> Materials {};

	UFUNCTION(BlueprintCallable,Category="Update")
	void UpdateWagonPos();

	UFUNCTION(BlueprintCallable,Category="Update")
	bool SetLocomotivePos();

	UFUNCTION(BlueprintCallable)
	void SetNewWagonColor(UStaticMeshComponent* NewWagon);

	float _trackDistance=0;

	UFUNCTION(BlueprintCallable)
	float GetWagonSize();

};
