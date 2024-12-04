// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plinth.h"
#include "Teletubbies.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Global/Select.h"
#include "Figurine.generated.h"


UCLASS()
class TOUTESTFAUX_API AFigurine : public ASelect, public ITeletubbies
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigurine();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* antMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* myPhysicCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetUpTeletubbies();

	UFUNCTION(BlueprintCallable,Category="Animations")
	void ChangeAnimation();

	UFUNCTION(BlueprintCallable,Category="Animations")
	int GetAnimationNumberToPlay();

	UFUNCTION(BlueprintCallable,Category="Animations")
	ETeletubbies GetMyTeletubbiesType();

	//Interface
	virtual ETeletubbies GetTeletubbiesType() override;
	virtual bool GetIfFigurineIsInRightPose() override;
	virtual void Clikcable() override;

private:
	UPROPERTY()
	AMainGameMode* _mainGameMode=nullptr;
	
	UPROPERTY(EditAnywhere,Category="Type of Teletubbies",meta=(AllowPrivateAccess))
	ETeletubbies _myTeletubbies = ETeletubbies::E_Po;
	int32 _poseIndex=0;
	int32 _rightPose;

	FTimerHandle TimerBeforeNextMove;
	bool bCanMove=true;
	
	UFUNCTION()
	void ChangeCanMove();
};

