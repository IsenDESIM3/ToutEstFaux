// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Door.h"
#include "Global/Select.h"
#include "Global/MainGameMode.h"
#include "Lock.generated.h"


enum class ETypeOfDoor : uint8;

USTRUCT(BlueprintType)
struct FLockData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numbers;

	UPROPERTY(EditAnywhere)
	float rot;
};
/**
 * 
 */
UCLASS()

class TOUTESTFAUX_API ALock : public ASelect
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ALock();
protected:
	virtual void BeginPlay() override;
public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* LockMesh;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring1;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring2;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring3;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring4;
	UPROPERTY()
	TArray<UStaticMeshComponent*> Meshes;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<FLockData> LockData;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<FLockData> Combination;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	bool bUnlock=false;

	UFUNCTION()
	void GetValueToRotation();
	UFUNCTION(BlueprintCallable)
	void CheckRotation();

	UFUNCTION()
	void Click(UPrimitiveComponent* TouchedComponent , FKey ButtonPressed);

private:
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess),Category="Type Of Locker")
	ETypeOfDoor MyTypeOfLockDoor = ETypeOfDoor::E_WardrobeDoor;
	
};




