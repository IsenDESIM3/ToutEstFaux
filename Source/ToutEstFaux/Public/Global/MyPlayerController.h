// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Gameplay/MyCharacters.h"
#include "Global/Select.h"
#include "Gameplay/Widget_Interaction.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMyPlayerController : public APlayerController 
{
	GENERATED_BODY()
	

	UPROPERTY()
	UWidget_Interaction* WidgetUse = nullptr;
	
	protected:
	virtual void BeginPlay() override;
	
	public:
	UFUNCTION(BlueprintCallable)
	void SwitchMappingContext(bool bIsOpen);
	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Interactor();
	UFUNCTION(BlueprintCallable)
	FVector2D GetGameResolution();
	UFUNCTION(BlueprintCallable)
	TScriptInterface<IISelectable> Raycast();
	UFUNCTION(BlueprintCallable)
	void GetMouseXYInfo(float mousex,float mousey);
	UFUNCTION()
	void HoldingKey();
	UFUNCTION()
	void StopHoldingKey();
	UFUNCTION()
	void ClicInInteraction();
	UFUNCTION()
	void PutDown();

	void SetWidget(UWidget_Interaction* newWidget);

	void SetInput(UEnhancedInputComponent* EIC,UEnhancedInputLocalPlayerSubsystem* Subsystem);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	FVector2D Result = FVector2D( 1, 1 );
	bool bCanRotate = false;
	bool bHandEmpty = true;
	bool bInputSwitched = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* defaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* interactionMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* mouseSelection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* holdingRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* clicInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* interaction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* releaseInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess = "true"))
	AMyCharacters* myCharacters;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess = "true"))
	AActor* ItemTarget; //Fill this variable with the Target variable of your item
	
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TScriptInterface<IISelectable> selected;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* _subsystem;

	

	//Temporaire
	bool bCantChangeMapping=true;
	FTimerHandle SwapMappingTimerHandle;
	void SetCanChangeMapping();
	
};
