// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateInput(FInputChord NewInput,FName Name);

	TArray<FEnhancedActionKeyMapping> GetKey();

private:
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* SubsystemPlayer=nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Mapping"))
	UInputMappingContext* defaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Mapping"))
	UInputMappingContext* interactionMappingContext;

	UPROPERTY()
	TArray<FEnhancedActionKeyMapping> AllMappingDefault{};
	
};
