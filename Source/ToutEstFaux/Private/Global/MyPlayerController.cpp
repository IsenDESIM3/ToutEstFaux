// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MyPlayerController.h"

#include "Chest.h"
#include "SkeletalDebugRendering.h"
#include "ViewportInteractionTypes.h"
#include "Global/ISelectable.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetGameResolution();
	WidgetUse = CreateWidget<UWidget_Interaction>(this, defaultWidget);
	WidgetUse->AddToViewport(0);
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(defaultMappingContext, 0);
		bShowMouseCursor = false;
	}
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(interaction, ETriggerEvent::Started, this , &AMyPlayerController::Interactor);
	}
	
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(mouseSelection, ETriggerEvent::Started, this , &AMyPlayerController::Grab);
	}
	
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(holdingRotation,ETriggerEvent::Started, this , &AMyPlayerController::HoldingKey);
		EnhancedInputComponent->BindAction(holdingRotation,ETriggerEvent::Completed, this , &AMyPlayerController::HoldingKey);
		EnhancedInputComponent->BindAction(holdingRotation,ETriggerEvent::Canceled, this , &AMyPlayerController::HoldingKey);
	}
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(clicInteraction,ETriggerEvent::Started, this , &AMyPlayerController::ClicInInteraction);
	}
	if(UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(releaseInteraction,ETriggerEvent::Started,this,&AMyPlayerController::PutDown);
	}
}

void AMyPlayerController::SwitchMappingContext(bool bIsOpen)
{
	
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(bIsOpen)
		{
			Subsystem->AddMappingContext(interactionMappingContext, 0);
			Subsystem->RemoveMappingContext(defaultMappingContext);
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
			Subsystem->AddMappingContext(defaultMappingContext,0);
			Subsystem->RemoveMappingContext(interactionMappingContext);
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

void AMyPlayerController::Grab()
{
	// 	TODO : mettre l'objet dans la main via une socket et faire la gestion d'inventaire
	if(!selected)
	selected = Raycast();
	if(selected!=nullptr && bHandEmpty)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Interactable");
		selected->Grabbed(myCharacters->itemPos);
		selected->SetInTheHand();
		ItemTarget = selected->GetItemTarget();
		bHandEmpty = false;
	}
	
}

void AMyPlayerController::Interactor()
{
	if(!selected)
	{
		selected = Raycast();
		if(selected!=nullptr)
		{
			SwitchMappingContext(true);
			selected->Shrink();
			selected->SetFrontCamera(myCharacters->GetCameraLocation()+myCharacters->GetCameraForward()*45);
		}
	}
	else
	{
		if(bHandEmpty)
		{
			SwitchMappingContext(false);
			selected->Increase();
			selected = nullptr;
		}
		else
		{
			if(!bInputSwitched)
			{
				SwitchMappingContext(true);
				selected->SetFrontCamera(myCharacters->GetCameraLocation()+myCharacters->GetCameraForward()*45);
				bInputSwitched = !bInputSwitched;
				myCharacters->SetActorRotation(FRotator(0,50,0));
			}
			else
			{
				SwitchMappingContext(false);
				selected->SetInTheHand();
				bInputSwitched = !bInputSwitched;
			}
		}
		
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
		if (target->Implements<UISelectable>() && myCharacters)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "beginning Shrink");
			return  TScriptInterface<IISelectable>(target);
		}
	}
	return nullptr;	
}


void AMyPlayerController::GetMouseXYInfo(float mousex, float mousey)
{
	if(selected && bCanRotate)
	{
		selected->NewRotation(FRotator(mousey,mousex,0)*-2);
		
	}
}

void AMyPlayerController::HoldingKey()
{
	bCanRotate = !bCanRotate;
}

void AMyPlayerController::ClicInInteraction()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Green,"Interactable");
	if(selected)
		selected->clickable();
}

void AMyPlayerController::PutDown()
{
	GetGameResolution();
	SetMouseLocation(Result.X, Result.Y);
	FVector MouseLocation, MouseForward;
	DeprojectMousePositionToWorld(MouseLocation, MouseForward);
	FHitResult HitResult;
	FVector EndRay = MouseLocation + MouseForward * 500.0f;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());
	FVector newpos;

	if(!bHandEmpty)
	{
		//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Main occupé");
		if(GetWorld()->LineTraceSingleByChannel(HitResult,MouseLocation,EndRay,ECC_Visibility,Params))
		{
			if(selected == nullptr) return;
			//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,"Selected est nul !!!");
			if (selected && HitResult.GetActor() == ItemTarget)
			{
				GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, HitResult.GetActor()->GetName());
				ItemTarget = HitResult.GetActor();
				if (ItemTarget->Implements<UInteractable>())
				{
					TScriptInterface<IInteractable> Target = TScriptInterface<IInteractable>(ItemTarget);
					Target->Interact();
					bHandEmpty = true;
					selected->Release(FVector(0,0,0));
					
					selected = nullptr;
					ItemTarget = nullptr;
				}
			}

				
			//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,HitResult.GetActor()->GetName());
			if(selected && HitResult.Distance<500.f)
			{
				//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Selected n'est pas nul");
				newpos = HitResult.Location;
				selected->Release(newpos);
				bHandEmpty = true;
				selected = nullptr;
				ItemTarget = nullptr;
			}
		}
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	myCharacters = Cast<AMyCharacters>(InPawn);
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
