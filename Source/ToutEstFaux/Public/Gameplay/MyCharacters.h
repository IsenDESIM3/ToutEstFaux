// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacters.generated.h"

class UWidget_Interaction;

UCLASS()
class TOUTESTFAUX_API AMyCharacters : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* itemPos;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;
	FVector GetCameraLocation();
	FVector GetCameraForward();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWidget_Interaction> defaultWidget= nullptr;

	
};
