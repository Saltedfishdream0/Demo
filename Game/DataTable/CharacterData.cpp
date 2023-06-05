// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterData.h"

FCharacterData::FCharacterData()
	: CharacterID(0),
	Health(100.f),
	MaxHealth(100.f),
	Mana(50.f),
	MaxMana(50.f),
	Stamina(50.f),
	MaxStamina(50.f),
	Exp(0.f),
	MaxExp(100.f),
	Level(1.f),
	Gold(0.f),
	Attack(20.f),
	Defense(10.f),
	AddHealth(50.f),
	AddMana(20.f),
	AddExp(200.f),
	AddAttack(50.f)
{
}
