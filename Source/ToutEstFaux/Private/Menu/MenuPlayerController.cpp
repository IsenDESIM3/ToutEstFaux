// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuPlayerController.h"
#include "EnhancedActionKeyMapping.h"


void AMenuPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	SubsystemPlayer=Subsystem;

	SubsystemPlayer->ClearAllMappings();

	SubsystemPlayer->AddMappingContext(interactionMappingContext,0);
	SubsystemPlayer->AddMappingContext(defaultMappingContext,1);
	
}

void AMenuPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(SubsystemPlayer)
	{
		if(!SubsystemPlayer->GetAllPlayerMappableActionKeyMappings().IsEmpty())
		{
			if(AllMappingDefault.IsEmpty())
			{
				AllMappingDefault=SubsystemPlayer->GetAllPlayerMappableActionKeyMappings();
			}
			
		}
	}
}

void AMenuPlayerController::UpdateInput(FInputChord NewInput,FName Name)
{
	if(SubsystemPlayer)
	{
		//Don't work
		//SubsystemPlayer->AddPlayerMappedKeyInSlot(Name,NewInput.Key);
	}
	
}

TArray<FEnhancedActionKeyMapping> AMenuPlayerController::GetKey()
{
	return AllMappingDefault;
}

