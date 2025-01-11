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
	
	void ChangeMenuMode(bool bNeedToChange);
	
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
	UInputMappingContext* MenuMappingContext;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* menuInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess = "true"))
	AMyCharacters* myCharacters;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess = "true"))
	AActor* ItemTarget; //Fill this variable with the Target variable of your item
	
	
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TScriptInterface<IISelectable> selected;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* _subsystem;

	

	//Anti Spam 
	bool bCantChangeMapping=true;
	FTimerHandle SwapMappingTimerHandle;
	void SetCanChangeMapping();

	bool bCanInteract=true;
	FTimerHandle InteractTimerHandle;
	void SetCanInteract();

	//LastMapping
	UInputMappingContext* LastMapping;
	UFUNCTION()
	void OpenCloseMenu();
	bool bIsMenuOpen=true;

	//Online
	//Grab
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_Grab();
	bool Server_Grab_Validate();
	void Server_Grab_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_Grab();
	bool Multi_Grab_Validate();
	void Multi_Grab_Implementation();

	//Interactor
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_Interactor();
	bool Server_Interactor_Validate();
	void Server_Interactor_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_Interactor();
	bool Multi_Interactor_Validate();
	void Multi_Interactor_Implementation();
	
	//Holding/NotHolding
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_HoldingKey();
	bool Server_HoldingKey_Validate();
	void Server_HoldingKey_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_HoldingKey();
	bool Multi_HoldingKey_Validate();
	void Multi_HoldingKey_Implementation();
	
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_StopHoldingKey();
	bool Server_StopHoldingKey_Validate();
	void Server_StopHoldingKey_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_StopHoldingKey();
	bool Multi_StopHoldingKey_Validate();
	void Multi_StopHoldingKey_Implementation();

	//Clic in Interaction
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_ClicInInteraction();
	bool Server_ClicInInteraction_Validate();
	void Server_ClicInInteraction_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_ClicInInteraction();
	bool Multi_ClicInInteraction_Validate();
	void Multi_ClicInInteraction_Implementation();

	//PutDown
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_PutDown();
	bool Server_PutDown_Validate();
	void Server_PutDown_Implementation();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_PutDown();
	bool Multi_PutDown_Validate();
	void Multi_PutDown_Implementation();

	//Rotate
	UFUNCTION(Server,Reliable,WithValidation,BlueprintCallable,Category="MultiPlayer")
	void Server_GetMouseXYInfo(float mousex, float mousey);
	bool Server_GetMouseXYInfo_Validate(float mousex, float mousey);
	void Server_GetMouseXYInfo_Implementation(float mousex, float mousey);

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void Multi_GetMouseXYInfo(float mousex, float mousey);
	bool Multi_GetMouseXYInfo_Validate(float mousex, float mousey);
	void Multi_GetMouseXYInfo_Implementation(float mousex, float mousey);

	UPROPERTY(editAnywhere, Category="Sound")
	USoundBase* GrabItemSound;
	UPROPERTY(editAnywhere, Category="Sound")
	USoundBase* PutDownItemSound;
};
