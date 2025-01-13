// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "PhotoFrame.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API APhotoFrame : public ASelect
{
	GENERATED_BODY()

public:
	APhotoFrame();
	virtual void BeginPlay() override;
	
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_ChangeMat();
	bool Server_ChangeMat_Validate();
	void Server_ChangeMat_Implementation();

protected:
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PhotoFrameMeshComponent;
	
private:
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	UMaterialInstance* SolutionMaterial;

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_ChangeMat();
	bool Multi_ChangeMat_Validate();
	void Multi_ChangeMat_Implementation();
	
	void ChangeMat();

	
};
