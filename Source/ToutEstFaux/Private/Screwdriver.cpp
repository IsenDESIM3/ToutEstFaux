// Fill out your copyright notice in the Description page of Project Settings.


#include "Screwdriver.h"


void AScrewdriver::Release(FVector newpos)
{
	Super::Release(newpos);
}

AActor* AScrewdriver::GetItemTarget()
{
	return Target;
}
