// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaBag.h"

	ATeaBag::ATeaBag()
	{
		TeaBagMesh = CreateDefaultSubobject<UStaticMeshComponent>("TeaBagMesh");
		TeaBagMesh->SetupAttachment(GetRootComponent());
		TeaBagMesh->SetRelativeLocation(FVector(0, 0, 0));
		TeaBagMesh->SetRelativeScale3D(FVector(1.5, 1.5, 1.5));

	}


void ATeaBag::Release(FVector newpos, FRotator newrot)
{
	Super::Release(newpos, newrot);
}

AActor* ATeaBag::GetItemTarget()
{
	return TeaCup;
}

FVector ATeaBag::GetReleasePos()
{
	return Super::GetReleasePos();
}
