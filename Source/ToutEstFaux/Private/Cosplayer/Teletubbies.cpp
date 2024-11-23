// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/Teletubbies.h"

#include "Cosplayer/Figurine.h"

// Add default functionality here for any ITeletubbies functions that are not pure virtual.
ETeletubbies ITeletubbies::GetTeletubbiesType()
{
	return ETeletubbies::E_Po;
}

bool ITeletubbies::GetIfFigurineIsInRightPose()
{
	return false;
}

