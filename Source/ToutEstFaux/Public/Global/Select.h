// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISelectable.h"
#include "GameFramework/Actor.h"
#include "Select.generated.h"

UCLASS()
class TOUTESTFAUX_API ASelect : public AActor, public  IISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Shrink(FVector cameraLocation) override;
	virtual void Increase() override;
	virtual void NewRotation(FRotator objectRotation) override;
	virtual void clicable() override;
	FVector inialLocation;
	FRotator initialRotation;
	UPROPERTY(EditAnywhere, Category="Components")
	UTexture2D* ImageReference;
	
	

};
