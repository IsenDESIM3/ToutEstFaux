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

	UPROPERTY(ReplicatedUsing=OnRep_DoorOpened)
	bool bIsDoorOpened=false;

	UFUNCTION()
	void OnRep_DoorOpened();

	int8 _multiplicateur=-1;
	
	void OpenTheDoor();
	void CloseTheDoor();

	FTimerHandle DoorHandler;

	FTimerHandle TestHandler;

	//Online
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_OpenTheDoor();
	bool Server_OpenTheDoor_Validate();
	void Server_OpenTheDoor_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_OpenTheDoor();
	bool Multi_OpenTheDoor_Validate();
	void Multi_OpenTheDoor_Implementation();

	UFUNCTION(Server,Reliable,WithValidation)
	void Server_CloseTheDoor();
	bool Server_CloseTheDoor_Validate();
	void Server_CloseTheDoor_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_CloseTheDoor();
	bool Multi_CloseTheDoor_Validate();
	void Multi_CloseTheDoor_Implementation();
};
