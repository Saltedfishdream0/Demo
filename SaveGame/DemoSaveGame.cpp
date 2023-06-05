// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoSaveGame.h"

FDemoPlayerData::FDemoPlayerData()
	: PlayerLevel(0),
	PlayerHealth(0),
	PlayerMana(0),
	PlayerExp(0),
	PlayerMaxExp(0),
	PlayerAttack(0)
{
}

UDemoSaveGame::UDemoSaveGame()
{
	SaveSlotName = TEXT("TextSaveSlot");
	UserIndex    = 0;
}
