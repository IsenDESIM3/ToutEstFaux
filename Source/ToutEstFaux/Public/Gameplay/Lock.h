// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Door.h"
#include "Global/Select.h"
#include "Lock.generated.h"


enum class ETypeOfDoor : uint8;

UENUM(BlueprintType)
enum class ETypeOfLock : uint8
{
	E_Ascii UMETA(DisplayName="Ascii Lock"),
	E_Number UMETA(DisplayName="Normal Lock"),
};

UENUM(BlueprintType)
enum class ENumbers : uint8
{
	E_1 UMETA(DisplayName="0 or 89"),
	E_0 UMETA(DisplayName="1 or 69"),
	E_9 UMETA(DisplayName="2 or 78"),
	E_8 UMETA(DisplayName="3 or 77"),
	E_7 UMETA(DisplayName="4 or 72"),
	E_6 UMETA(DisplayName="5 or 74"),
	E_5 UMETA(DisplayName="6 or 90"),
	E_4 UMETA(DisplayName="7 or 75"),
	E_3 UMETA(DisplayName="8 or 87"),
	E_2 UMETA(DisplayName="9 or 84"),
};
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLockData
{
	
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENumbers numbers;
	
	float rot;
};
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
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Lock")
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

	virtual void Release(FVector newpos, FRotator newrot) override;

	UFUNCTION(BlueprintCallable)
	void ChangeMat(UMaterialInstance* NewMat);

	UPROPERTY(editAnywhere, Category="Sound")
	USoundBase* Unlocked;

private:
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess),Category="Type Of Locker")
	ETypeOfDoor MyTypeOfLockDoor = ETypeOfDoor::E_WardrobeDoor;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess),Category="Type Of Locker")
	ETypeOfLock MyLock = ETypeOfLock::E_Ascii;

	FVector _initialPos;
	FRotator _initialRot;
	
};




