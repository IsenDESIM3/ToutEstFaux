// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaBag.h"

void ATeaBag::Release(FVector newpos, FRotator newrot)
{
	Super::Release(newpos, newrot);
}

AActor* ATeaBag::GetItemTarget()
{
	return TeaCup;
}
