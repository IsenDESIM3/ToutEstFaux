// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class ETypeOfOpening : uint8
{
	E_FrontOpening UMETA(DisplayName="Front Opening"),
	E_BackOpening UMETA(DisplayName="Back Opening"),
	
};
UENUM(BlueprintType)
enum class ETypeOfDoor : uint8
{
	E_NormalDoor UMETA(DisplayName="Normal Door"),
	E_ExitDoor UMETA(DisplayName="Exit Door"),
	E_WardrobeDoor UMETA(DisplayName="Wardrobe Door"),
	
};
UCLASS()
class TOUTESTFAUX_API ADoor : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Door;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SetOpenDoor();
	ETypeOfDoor GetTypeOfDoor();

private:
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	ETypeOfOpening TypeOfOpening=ETypeOfOpening::E_FrontOpening;
	
	float _maxRotation=90.f;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	ETypeOfDoor MyTypeOfDoor=ETypeOfDoor::E_NormalDoor;

	UPROPERTY(ReplicatedUsing=OnRep_DoorOpened)
	bool bIsDoorOpened=false;

	UFUNCTION()
	void OnRep_DoorOpened();

	UPROPERTY(ReplicatedUsing=OnRep_ChangeRot)
	float _actualRotation=0;

	UFUNCTION()
	void OnRep_ChangeRot();

	int8 _multiplicator=-1;
	float _RotationGoal=0;
	
	void OpenTheDoor();

	FTimerHandle DoorHandler;
	
};
