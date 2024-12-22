// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MyPlayerController.h"

#include <string>

#include "Chest.h"
#include "IPlaceable.h"
#include "SkeletalDebugRendering.h"
#include "ViewportInteractionTypes.h"
#include "Global/ISelectable.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::SetInput(UEnhancedInputComponent* EIC,UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	if(EIC)
	{
		EIC->BindAction(interaction,ETriggerEvent::Started, this , &AMyPlayerController::Server_Interactor);
		EIC->BindAction(mouseSelection,ETriggerEvent::Started, this , &AMyPlayerController::Server_Grab);
		EIC->BindAction(holdingRotation,ETriggerEvent::Started, this , &AMyPlayerController::Server_HoldingKey);
		EIC->BindAction(holdingRotation,ETriggerEvent::Completed, this , &AMyPlayerController::Server_StopHoldingKey);
		EIC->BindAction(holdingRotation,ETriggerEvent::Canceled, this , &AMyPlayerController::Server_StopHoldingKey);
		EIC->BindAction(clicInteraction,ETriggerEvent::Started, this , &AMyPlayerController::Server_ClicInInteraction);
		EIC->BindAction(releaseInteraction,ETriggerEvent::Started,this,&AMyPlayerController::Server_PutDown);
	}

	_subsystem=Subsystem;
	
	
}


void AMyPlayerController::SwitchMappingContext(bool bIsOpen)
{
	
	if(_subsystem)
	{
		_subsystem->ClearAllMappings();
		
		if(bIsOpen)
		{
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,"Interaction mode");
			_subsystem->AddMappingContext(interactionMappingContext, 0);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Blue,"Normal mode");
			_subsystem->AddMappingContext(defaultMappingContext,0);
		}
	}
}


bool AMyPlayerController::Server_Grab_Validate()
{
	return true;
}

void AMyPlayerController::Server_Grab_Implementation()
{
	
	Multi_Grab();
}

bool AMyPlayerController::Multi_Grab_Validate()
{
	return true;
}

void AMyPlayerController::Multi_Grab_Implementation()
{
	
	Grab();
}

void AMyPlayerController::Grab()
{
	
	// 	TODO : mettre l'objet dans la main via une socket et faire la gestion d'inventaire
	if(!selected)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Blue,"Pas de Seclected");
		selected = Raycast();
	}
	if(selected!=nullptr && bHandEmpty)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Interactable");
		selected->Grabbed(myCharacters->itemPos);
		selected->SetInTheHand();
		ItemTarget = selected->GetItemTarget();
		bHandEmpty = false;
	}
	
}

bool AMyPlayerController::Server_Interactor_Validate()
{
	return true;
}

void AMyPlayerController::Server_Interactor_Implementation()
{
	Multi_Interactor();
}

bool AMyPlayerController::Multi_Interactor_Validate()
{
	return true;
}

void AMyPlayerController::Multi_Interactor_Implementation()
{
	Interactor();
}


void AMyPlayerController::Interactor()
{
	
	FVector CameraLocation = myCharacters->GetCameraLocation();
	FRotator CameraRotation = myCharacters->GetControlRotation(); 

	FRotator NewRotation = FRotator(CameraRotation.Pitch, CameraRotation.Yaw, 0.0f);

	myCharacters->Controller->SetControlRotation(NewRotation);

	FVector ForwardVector = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);

	FVector ItemPosition = CameraLocation + (ForwardVector * 60.0f);

	if(!selected)
	{
		selected = Raycast();
		if(selected!=nullptr)
		{
			SwitchMappingContext(true);
			selected->Shrink();
			selected->SetFrontCamera(ItemPosition);
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
			if(bCantChangeMapping)
			{
				bCantChangeMapping=false;
				GetWorldTimerManager().SetTimer(SwapMappingTimerHandle,this,&AMyPlayerController::SetCanChangeMapping,0.2f);
				
				if(!bInputSwitched)
				{
					GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,"Input Not switch");
					SwitchMappingContext(true);
					selected->SetFrontCamera(ItemPosition);
					bInputSwitched = !bInputSwitched;
					
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1,2,FColor::Blue,"Input switch");
					SwitchMappingContext(false);
					selected->SetInTheHand();
					bInputSwitched = !bInputSwitched;
				}
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

bool AMyPlayerController::Server_GetMouseXYInfo_Validate(float mousex, float mousey)
{
	return true;
}

void AMyPlayerController::Server_GetMouseXYInfo_Implementation(float mousex, float mousey)
{
	Multi_GetMouseXYInfo(mousex,mousey);
}

bool AMyPlayerController::Multi_GetMouseXYInfo_Validate(float mousex, float mousey)
{
	return true;
}

void AMyPlayerController::Multi_GetMouseXYInfo_Implementation(float mousex, float mousey)
{
	GetMouseXYInfo(mousex,mousey);
}

void AMyPlayerController::GetMouseXYInfo(float mousex, float mousey)
{
	if(selected && bCanRotate)
	{
		selected->NewRotation(FRotator(mousey,mousex,0)*-2);
	}
}

bool AMyPlayerController::Server_HoldingKey_Validate()
{
	return true;
}

void AMyPlayerController::Server_HoldingKey_Implementation()
{
	Multi_HoldingKey();
}

bool AMyPlayerController::Multi_HoldingKey_Validate()
{
	return true;
}

void AMyPlayerController::Multi_HoldingKey_Implementation()
{
	HoldingKey();
}

void AMyPlayerController::HoldingKey()
{
	bCanRotate = true;
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,"Can Rotate");
}

bool AMyPlayerController::Server_StopHoldingKey_Validate()
{
	return true;
}

void AMyPlayerController::Server_StopHoldingKey_Implementation()
{
	Multi_StopHoldingKey();
}

bool AMyPlayerController::Multi_StopHoldingKey_Validate()
{
	return true;
}

void AMyPlayerController::Multi_StopHoldingKey_Implementation()
{
	StopHoldingKey();
}

void AMyPlayerController::StopHoldingKey()
{
	bCanRotate = false;
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,"Cannot Rotate");
}

bool AMyPlayerController::Server_ClicInInteraction_Validate()
{
	return true;
}

void AMyPlayerController::Server_ClicInInteraction_Implementation()
{
	Multi_ClicInInteraction();
}

bool AMyPlayerController::Multi_ClicInInteraction_Validate()
{
	return true;
}

void AMyPlayerController::Multi_ClicInInteraction_Implementation()
{
	ClicInInteraction();
}

void AMyPlayerController::ClicInInteraction()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Green,"Interactable");
	if(selected && bCanInteract)
	{
		selected->Clickable();
		bCanInteract=false;
		GetWorldTimerManager().SetTimer(InteractTimerHandle,this,&AMyPlayerController::SetCanInteract,0.1f);
	}
		
}

void AMyPlayerController::SetCanInteract()
{
	bCanInteract=true;
}


bool AMyPlayerController::Server_PutDown_Validate()
{
	return true;
}

void AMyPlayerController::Server_PutDown_Implementation()
{
	Multi_PutDown();
}

bool AMyPlayerController::Multi_PutDown_Validate()
{
	return true;
}

void AMyPlayerController::Multi_PutDown_Implementation()
{
	PutDown();
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

	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Blue,"PutDown");

	if(!bHandEmpty)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Main occupé");
		if(GetWorld()->LineTraceSingleByChannel(HitResult,MouseLocation,EndRay,ECC_Visibility,Params))
		{
			if(selected == nullptr) return;
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,"Selected est nul !!!");
			if (HitResult.GetActor() == ItemTarget)
			{
				GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, HitResult.GetActor()->GetName());
				ItemTarget = HitResult.GetActor();
				if (ItemTarget->Implements<UInteractable>())
				{
					TScriptInterface<IInteractable> Target = TScriptInterface<IInteractable>(ItemTarget);
					Target->Interact();
					bHandEmpty = true;
					selected->Release(FVector(0,0,0), FRotator(0,myCharacters->GetControlRotation().Yaw,0));
				
					selected = nullptr;
					ItemTarget = nullptr;
				}
				
			}
			else if (HitResult.GetActor()->Implements<UIPlaceable>())
			{
				TScriptInterface<IIPlaceable> Target = TScriptInterface<IIPlaceable>(HitResult.GetActor());
				float actorHeight = Target->getActorHeight();
				
				//newpos = FVector(HitResult.GetActor()->GetActorLocation().X, HitResult.GetActor()->GetActorLocation().Y, actorHeight-10);
				newpos = FVector(HitResult.Location.X, HitResult.Location.Y, actorHeight);
				selected->Release(newpos+myCharacters->GetCameraForward(), FRotator(0,myCharacters->GetControlRotation().Yaw,0));
				bHandEmpty = true;
				selected = nullptr;
				ItemTarget = nullptr;
			}
			// 	
			// if(HitResult.Distance<500.f)
			// {
			// 	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,"Selected n'est pas nul");
			// 	newpos = HitResult.Location;
			// 	selected->Release(newpos);
			// 	bHandEmpty = true;
			// 	selected = nullptr;
			// 	ItemTarget = nullptr;
			// }
		}
	}
}

void AMyPlayerController::SetWidget(UWidget_Interaction* newWidget)
{
	WidgetUse = newWidget;
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	myCharacters = Cast<AMyCharacters>(InPawn);

	GetGameResolution();
	
}

void AMyPlayerController::SetCanChangeMapping()
{
	bCantChangeMapping=true;
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
