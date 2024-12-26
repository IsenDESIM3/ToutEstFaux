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
	virtual auto Shrink() -> void override;
	virtual void Increase() override;
	virtual void NewRotation(FRotator objectRotation) override;
	virtual void Clickable() override;
	virtual void Grabbed(UStaticMeshComponent* mesh) override;
	virtual void Release(FVector newpos, FRotator newrot) override;
	virtual void SetFrontCamera(FVector vector) override;
	virtual void SetInTheHand() override;
	virtual AActor* GetItemTarget() override;
	FVector inialLocation;
	FRotator initialRotation;
	UPROPERTY(EditAnywhere, Category="Selection Info")
	UTexture2D* ImageReference;
	
	UPROPERTY(EditDefaultsOnly, Category="Selection Info")
	float GrabbedScale=0.4f;

};
