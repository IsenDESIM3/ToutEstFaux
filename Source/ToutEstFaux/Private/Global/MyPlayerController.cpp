// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MyPlayerController.h"

#include "Global/ISelectable.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	
	bShowMouseCursor = true;
}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MouseSelection, ETriggerEvent::Started, this , &AMyPlayerController::Selection);
	}
}

void AMyPlayerController::Selection()
{
	FVector MouseLocation, MouseForward;
	DeprojectMousePositionToWorld(MouseLocation, MouseForward);
	FHitResult HitResult;
	FVector EndRay = MouseLocation + MouseForward * 1000.0f;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	if(GetWorld()->LineTraceSingleByChannel(HitResult,MouseLocation,EndRay,ECC_Visibility,Params))
	{
		AActor* TargetActor = HitResult.GetActor();
		//if(ADamePawn* Pions = Cast<ADamePawn>(HitResult.GetActor()))
		if(TargetActor->Implements<UISelectable>())
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Interactable");
		else
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,"Not Interactable");
	}
}
