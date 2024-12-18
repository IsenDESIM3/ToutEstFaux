// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "Book.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API ABook : public ASelect
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Clickable() override;
	virtual void Release(FVector newpos, FRotator newrot) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	bool bIsOpen = false;
};
