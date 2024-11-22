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
	virtual void SetupInputComponent() override;
	
	public:
	UFUNCTION(BlueprintCallable)
	void SwitchMappingContext(bool bIsOpen);
	UFUNCTION(BlueprintCallable)
	void Selection();
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
	void ClicInInteraction();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UWidget_Interaction> interactionWidget = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UWidget_Interaction> defaultWidget= nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	FVector2D Result = FVector2D( 1, 1 );
	bool bCanRotate = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* InteractionMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MouseSelection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* HoldingRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* clicInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* Interaction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess = "true"))
	AMyCharacters* MyCharacters;
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TScriptInterface<IISelectable> Selected;
	
	
	
};
