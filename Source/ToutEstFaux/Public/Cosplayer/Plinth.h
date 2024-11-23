// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teletubbies.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Plinth.generated.h"

enum class ETeletubbies : uint8;

UCLASS()
class TOUTESTFAUX_API APlinth : public AActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* plinthCollider;
	
public:	
	// Sets default values for this actor's properties
	APlinth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//Put in Game Mode
	void CheckIfFigurineIsGood();

	//Put in Game Mode
	void RemoveFigurine();

	UPROPERTY()
	TScriptInterface<ITeletubbies> _figurine;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	ETeletubbies _myTeletubbiesType;
	
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrontSweep, const FHitResult& SweepResult );

	
	UFUNCTION()
	void OnOverlapedEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

};
