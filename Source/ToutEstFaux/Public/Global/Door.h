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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetOpenDoor();
	

private:
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	ETypeOfOpening TypeOfOpening=ETypeOfOpening::E_FrontOpening;
	
	float _maxRotation=90.f;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	bool bIsAnExitDoor=true;
	
	bool bIsDoorOpened=false;

	int8 _multiplicateur=1;
	
	void OpenTheDoor();
	void CloseTheDoor();

	FTimerHandle DoorHandler;

	FTimerHandle TestHandler;
};
