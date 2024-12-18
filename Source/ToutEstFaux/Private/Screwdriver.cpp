// Fill out your copyright notice in the Description page of Project Settings.


#include "Screwdriver.h"


void AScrewdriver::Release(FVector newpos, FRotator newrot)
{
	Super::Release(newpos, newrot);
}

AActor* AScrewdriver::GetItemTarget()
{
	return Target;
}
