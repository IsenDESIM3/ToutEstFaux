// Fill out your copyright notice in the Description page of Project Settings.


#include "Book.h"




void ABook::Clickable()
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


	Super::Clickable();
}

void ABook::Release(FVector newpos, FRotator newrot)
{
	Super::Release(newpos, newrot);
	SetActorLocation(FVector(newpos.X, newpos.Y, newpos.Z+5));
	SetActorRotation(FRotator(-90, newrot.Yaw, newrot.Roll));
}
