// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaKettle.h"

AActor* ATeaKettle::GetItemTarget()
{
	return TeaCup;
}

FVector ATeaKettle::GetReleasePos()
{
	return FVector(0, 0, 0);
}
