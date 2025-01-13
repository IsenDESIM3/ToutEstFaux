// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MappingUI.h"
#include "Menu/MenuGameMode.h"

void UMappingUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMappingUI::InputChange(FKey NewInput)
{
	if(_menuGameMode)
	{
		_menuGameMode->ChangeInput(NewInput,FName(Txt_Commande->GetText().ToString()));
	}
}


void UMappingUI::SetWidget(FText Text, FKey NewKey,AMenuGameMode* GameMode)
{
	Txt_Commande->SetText(Text);
	
	FInputChord Input = Iks_Input->GetSelectedKey();
	Input.Key=NewKey;
	
	Iks_Input->SetSelectedKey(Input);

	_menuGameMode=GameMode;
}


