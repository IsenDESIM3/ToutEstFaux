// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Figurine.generated.h"

UENUM(BlueprintType)
enum class ETeletubbies : uint8
{
	E_Po UMETA(DisplayName="Po_Red"),
	E_Dispy UMETA(DisplayName="Dispy_Green"),
	E_Laalaa UMETA(DisplayName="Laalaa_Yellow"),
	E_Tinkywinky UMETA(DisplayName="Tinkywinky")
};

USTRUCT(BlueprintType)
struct FTeletubbiesMatData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	ETeletubbies Teletubbies=ETeletubbies::E_Po;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* BodyMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* EarMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* FaceMat=nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Teletubbies_Ant_Mesh=nullptr;

	UPROPERTY(EditAnywhere)
	int32 GoodPoseNumber;
	
};
UCLASS()
class TOUTESTFAUX_API AFigurine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigurine();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Ant_Mesh;

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

private:
	UPROPERTY(EditDefaultsOnly,Category="All Teletubbies Configuration",meta=(AllowPrivateAccess))
	TArray<FTeletubbiesMatData> ListOfTeletubbiesMatData{};
	
	UPROPERTY(EditAnywhere,Category="Type of Teletubbies",meta=(AllowPrivateAccess))
	ETeletubbies MyTeletubbies = ETeletubbies::E_Po;

	UPROPERTY()
	TArray<int32> AllAnimationsPosible{1,2,3,4};

	int32 ActualAnimationNumber=-1;

	int32 index=-1;

	int32 RightPose;
};

