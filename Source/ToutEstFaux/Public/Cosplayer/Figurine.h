// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teletubbies.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Figurine.generated.h"

//Put in Game Mode
UENUM(BlueprintType)
enum class ETeletubbies : uint8
{
	E_Po UMETA(DisplayName="Po_Red"),
	E_Dispy UMETA(DisplayName="Dispy_Green"),
	E_Laalaa UMETA(DisplayName="Laalaa_Yellow"),
	E_Tinkywinky UMETA(DisplayName="Tinkywinky")
};

//Put in Game Mode
USTRUCT(BlueprintType)
struct FTeletubbiesMatData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	ETeletubbies teletubbies=ETeletubbies::E_Po;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* bodyMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* earMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* faceMat=nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* teletubbiesAntMesh=nullptr;

	UPROPERTY(EditAnywhere)
	int32 goodPoseNumber;
	
};
UCLASS()
class TOUTESTFAUX_API AFigurine : public AActor, public ITeletubbies
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

private:
	
	//Put in Game Mode
	UPROPERTY(EditDefaultsOnly,Category="All Teletubbies Configuration",meta=(AllowPrivateAccess))
	TArray<FTeletubbiesMatData> _listOfTeletubbiesMatData{};
	
	UPROPERTY(EditAnywhere,Category="Type of Teletubbies",meta=(AllowPrivateAccess))
	ETeletubbies _myTeletubbies = ETeletubbies::E_Po;

	int32 _poseIndex=0;

	int32 _rightPose;
	
};

