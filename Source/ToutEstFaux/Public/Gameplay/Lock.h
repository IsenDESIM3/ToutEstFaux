// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "Lock.generated.h"

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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* LockMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	UStaticMeshComponent* Ring4;
	TArray<UStaticMeshComponent*> Meshes;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<int> Combination;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<float> goodRot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<float> rot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	TArray<bool> locked;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lock")
	bool bUnlock=false;

	UFUNCTION()
	void GetValueToRotation();
	UFUNCTION(BlueprintCallable)
	void CheckRotation(int index);
	
};
