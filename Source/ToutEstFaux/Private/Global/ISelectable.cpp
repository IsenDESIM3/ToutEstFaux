// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/ISelectable.h"


void IISelectable::Shrink()
{
	
}

void IISelectable::Grabbed(UStaticMeshComponent* mesh)
{
	
}

void IISelectable::Release(FVector newpos, FRotator newrot)
{
	
}

void IISelectable::SetFrontCamera(FVector vector)
{
}

void IISelectable::SetInTheHand()
{
	
}


void IISelectable::Increase()
{
	
}

void IISelectable::NewRotation(FRotator objectRotation)
{
	
}

void IISelectable::Clickable()
{
}

AActor* IISelectable::GetActor()
{
	return nullptr;
}

AActor* IISelectable::GetItemTarget()
{
	return nullptr;
}

FVector IISelectable::GetReleasePos()
{
	return FVector(0,0,0);
}
