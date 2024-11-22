// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MyPlayerController.h"

#include "Global/ISelectable.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetGameResolution();
	WidgetUse = CreateWidget<UWidget_Interaction>(this, defaultWidget);
	WidgetUse->AddToViewport(0);
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		bShowMouseCursor = false;
	}
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Started, this , &AMyPlayerController::Interactor);
	}
	
	Super::SetupInputComponent();
	// if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	// {
	// 	EnhancedInputComponent->BindAction(MouseSelection, ETriggerEvent::Started, this , &AMyPlayerController::Selection);
	// }
	
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(HoldingRotation,ETriggerEvent::Started, this , &AMyPlayerController::HoldingKey);
		EnhancedInputComponent->BindAction(HoldingRotation,ETriggerEvent::Completed, this , &AMyPlayerController::HoldingKey);
		EnhancedInputComponent->BindAction(HoldingRotation,ETriggerEvent::Canceled, this , &AMyPlayerController::HoldingKey);
	}
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(clicInteraction,ETriggerEvent::Started, this , &AMyPlayerController::ClicInInteraction);
	}
}

void AMyPlayerController::SwitchMappingContext(bool bIsOpen)
{
	
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(bIsOpen)
		{
			Subsystem->AddMappingContext(InteractionMappingContext, 0);
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			if (IsValid(interactionWidget))
			{
				bShowMouseCursor = true;
				WidgetUse->RemoveFromParent();
				// WidgetUse = CreateWidget<UWidget_Interaction>(this, interactionWidget);
				// WidgetUse->AddToViewport(0);
			}
		}
		else
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
			Subsystem->RemoveMappingContext(InteractionMappingContext);
			if (IsValid(defaultWidget))
			{
				bShowMouseCursor = false;
				// WidgetUse->RemoveFromParent();
				WidgetUse = CreateWidget<UWidget_Interaction>(this, defaultWidget);
				WidgetUse->AddToViewport(0);
			}
		}
	}
}

void AMyPlayerController::Selection()
{
	
	// 	TODO : mettre l'objet dans la main via une socket et faire la gestion d'inventaire
	if(Raycast()!=nullptr)
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Interactable");
	else
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,"Not Interactable");
}

void AMyPlayerController::Interactor()
{
	if(!Selected)
	{
		Selected = Raycast();
		if(Selected!=nullptr)
		{
			SwitchMappingContext(true);
			Selected->Shrink(MyCharacters->GetCameraLocation()+MyCharacters->GetCameraForward()*100);
		}
	}
	else
	{
		SwitchMappingContext(false);
		Selected->Increase();
		Selected = nullptr;
	}
		
}

TScriptInterface<IISelectable> AMyPlayerController::Raycast()
{
	GetGameResolution();
	SetMouseLocation(Result.X, Result.Y);
	FVector MouseLocation, MouseForward;
	DeprojectMousePositionToWorld(MouseLocation, MouseForward);
	FHitResult HitResult;
	FVector EndRay = MouseLocation + MouseForward * 500.0f;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	
	if(GetWorld()->LineTraceSingleByChannel(HitResult,MouseLocation,EndRay,ECC_Visibility,Params))
	{
		AActor* target = HitResult.GetActor();
		if (target->Implements<UISelectable>() && MyCharacters)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "beginning Shrink");
			return  TScriptInterface<IISelectable>(target);
		}
	}
	return nullptr;	
}


void AMyPlayerController::GetMouseXYInfo(float mousex, float mousey)
{
	if(Selected && bCanRotate)
	{
		Selected->NewRotation(FRotator(mousey,mousex,0)*-2);
		
	}
}

void AMyPlayerController::HoldingKey()
{
	bCanRotate = !bCanRotate;
}

void AMyPlayerController::ClicInInteraction()
{
	if(Selected)
		Selected->clicable();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MyCharacters = Cast<AMyCharacters>(InPawn);
}


FVector2D AMyPlayerController::GetGameResolution()
{
	if ( GEngine && GEngine->GameViewport )
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result );
	}

	Result.X /= 2;
	Result.Y /= 2;
	return Result;
}
