// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaCup.h"

#include "Global/MainGameState.h"


ATeaCup::ATeaCup()
{

	TeaCupLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeaCupLocation"));
	TeaCupLocation->SetupAttachment(GetRootComponent());
	TeaCupLocation->SetRelativeLocation(FVector(0, 0, 0));

	
	TeaBagLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeaBagLocation"));
	TeaBagLocation->SetupAttachment(TeaCupLocation);
	TeaBagLocation->SetRelativeLocation(FVector(3, -2, 5));
	TeaBagLocation->SetRelativeRotation(FRotator(20, 0, 0));
	TeaBagLocation->SetRelativeScale3D(FVector(.8, .8,.8));

	
}

void ATeaCup::Interact()
{

	if (Cast<ATeaBag>(MyPlayerController->selected->GetActor()))
	{
		if (bHasTeaBag) return;
		TeaBag = Cast<ATeaBag>(MyPlayerController->selected->GetActor());
		if (TeaBag->Tags[0] == "TeaBag")
		{
			TeaBagLocation->SetStaticMesh(TeaBag->TeaBagMesh->GetStaticMesh());
			TeaBagLocation->SetMaterial(0, TeaBag->TeaBagMesh->GetMaterial(0));
			bHasTeaBag = true;
			//GEngine->AddOnScreenDebugMessage(-1,1, FColor::Red, TeaBag->GetName());
			
		}
	}
	
	if (Cast<ATeaKettle>(MyPlayerController->selected->GetActor()))
	{
		if(TeaBag)
		{
			bIsFilled = true;
			
			if(PutWaterSound)
			{
				PlayAudio(PutWaterSound);
			}
			

			if (TeaBag->Tags[1] == "Green")
			{
				TeaCupLocation->SetMaterial(1, TeaCupCorrectMaterial);
				TeaCupLocation->SetMaterial(2, TeaLiquidMaterial);
				TeaBagLocation->SetStaticMesh(nullptr);
				TeaBag = nullptr;

				ShowKlaket();
			}
			else
			{
				TeaCupLocation->SetMaterial(2, TeaLiquidMaterial);
				TeaBagLocation->SetStaticMesh(nullptr);
				TeaBag = nullptr;
			}
		}
		
	}
	
	IInteractable::Interact();
}

void ATeaCup::Clickable()
{
	if (bIsFilled)
	{
		if(DrinkSound)
		{
			PlayAudio(DrinkSound);
		}
		
		TeaCupLocation->SetMaterial(2, TeaLiquidBaseMaterial);
		bHasTeaBag = false;
		bIsFilled = false;
		TeaBag = nullptr;
		TeaBagLocation->SetStaticMesh(nullptr);
	}
	Super::Clickable();
}

bool ATeaCup::bCanInteract()
{
	return TeaBag ? false : true;
}

void ATeaCup::ShowKlaket()
{
	if(!bIsKlaketUp)
	{
		if(AMainGameState* GS = Cast<AMainGameState>(GetWorld()->GetGameState()))
		{
			GS->ShowKlakets();
			bIsKlaketUp=true;
		}
	}
	
}

