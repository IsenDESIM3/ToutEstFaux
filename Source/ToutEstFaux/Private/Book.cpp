// Fill out your copyright notice in the Description page of Project Settings.


#include "Book.h"




void ABook::clickable()
{
	if (!bIsOpen)
	{
		SetActorRotation(FRotator(0, 0, 0));
		StaticMesh->SetRelativeRotation(FRotator(0, -150, 0));
		bIsOpen = !bIsOpen;
	}
	else
	{
		SetActorRotation(FRotator(0, 0, 0));
		StaticMesh->SetRelativeRotation(FRotator(0 ,0 , 0));
		bIsOpen = !bIsOpen;
	}


	Super::clickable();
}
