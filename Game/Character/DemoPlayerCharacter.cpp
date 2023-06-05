// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoPlayerCharacter.h"

#include "DemoEnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Game/Ability/AttributeSet/DemoAttributeSet.h"
#include "Game/Component/FightComponent.h"
#include "Game/Core/GameState/DemoGameStateBase.h"
#include "Game/Core/HUD/DemoHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/GameUI/GameMainUI.h"

//////////////////////////////////////////////////////////////////////////
// ADemoCharacter

ADemoPlayerCharacter::ADemoPlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;                         // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate              = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity              = 700.f;
	GetCharacterMovement()->AirControl                 = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed               = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed         = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength         = 400.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true;   // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;                              // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//背部武器场景组件
	Back_Weapon = CreateDefaultSubobject<USceneComponent>("Back_Weapon");
	//Back_Weapon->SetupAttachment(GetMesh());
	Back_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Weapon_Back");

	//手部武器场景组件
	Hand_Weapon = CreateDefaultSubobject<USceneComponent>("Hand_Weapon");
	//Hand_Weapon->SetupAttachment(GetMesh());
	Hand_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Weapon_Hand");

	//武器骨骼
	Weapon_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon_Mesh");
	Weapon_Mesh->SetupAttachment(Back_Weapon);
}

void ADemoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, & ADemoPlayerCharacter::Update, 0.01f, false);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADemoPlayerCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, & ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, & ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, & ADemoPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, & ADemoPlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, & APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, & APawn::AddControllerPitchInput);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, & ADemoPlayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, & ADemoPlayerCharacter::TouchStopped);

	//绑定奔跑按键
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, & ADemoPlayerCharacter::SetStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, & ADemoPlayerCharacter::SetEndRun);

	//绑定切换状态
	PlayerInputComponent->BindAction("Exchange_Weapons", IE_Pressed, this, & ADemoPlayerCharacter::StateSwitching);

	//绑定攻击
	PlayerInputComponent->BindAction("ComboAttack", IE_Pressed, this, & ADemoPlayerCharacter::BeginComboAttack);
	PlayerInputComponent->BindAction("ComboAttack", IE_Released, this, & ADemoPlayerCharacter::EndComboAttack);

	//绑定背包打开和关闭
	PlayerInputComponent->BindAction("BackPack", IE_Pressed, this, & ADemoPlayerCharacter::ControlBackPack);

	//绑定属性面板打开和关闭
	PlayerInputComponent->BindAction("AttributePanel", IE_Pressed, this, & ADemoPlayerCharacter::ControlAttributePanel);

	//绑定保存和加载游戏面板
	PlayerInputComponent->BindAction("SaveAndLoadGame", IE_Pressed, this, & ADemoPlayerCharacter::ControlSaveAndLoadPanel);
}

void ADemoPlayerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ADemoPlayerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ADemoPlayerCharacter::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADemoPlayerCharacter::MoveRight(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ADemoPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADemoPlayerCharacter::SetStartRun()
{
	RunSpeed                             = 800.f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ADemoPlayerCharacter::SetEndRun()
{
	RunSpeed                             = 500.f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ADemoPlayerCharacter::StateSwitching()
{
	if(StateMontage)
	{
		PlayAnimMontage(StateMontage);
		GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, & ADemoPlayerCharacter::CleanTime, 0.7f, false);
	}
}

void ADemoPlayerCharacter::CleanTime()
{
	GetWorld()->GetTimerManager().ClearTimer(MonitorTimer);
	//默认在背上
	//从背上拿到手上
	if(!bStateSwitch)
	{
		Weapon_Mesh->AttachToComponent(Hand_Weapon, FAttachmentTransformRules::KeepWorldTransform);
		Weapon_Mesh->SetRelativeTransform(FTransform());

		bStateSwitch = true;
		return;
	}
	//从手上回到背上
	else if(bStateSwitch)
	{
		//PlayAnimMontage(StateMontage);

		Weapon_Mesh->AttachToComponent(Back_Weapon, FAttachmentTransformRules::KeepWorldTransform);
		Weapon_Mesh->SetRelativeTransform(FTransform());

		bStateSwitch = false;
		return;
	}
}

void ADemoPlayerCharacter::BeginComboAttack()
{
	if(!bStateSwitch)
	{
		return;
	}

	GetFightComponents()->ComboAttackPressed();
}

void ADemoPlayerCharacter::EndComboAttack()
{
	GetFightComponents()->ComboAttackReleased();
}

void ADemoPlayerCharacter::UpdateHealth(float Value)
{
	UpdateHealthProgressBar.ExecuteIfBound(Value);
}

void ADemoPlayerCharacter::UpdateMana(float Value)
{
	UpdateManaProgressBar.ExecuteIfBound(Value);
}

void ADemoPlayerCharacter::UpdateStamina(float Value)
{
	UpdateStaminaProgressBar.ExecuteIfBound(Value);
}

void ADemoPlayerCharacter::UpdateExp(float Value)
{
	UpdateExpProgressBar.ExecuteIfBound(Value);
}

void ADemoPlayerCharacter::UpdateLevel(float Value)
{
	UpdateLevelText.ExecuteIfBound(Value);
}

void ADemoPlayerCharacter::Update()
{
	GetWorld()->GetTimerManager().ClearTimer(MonitorTimer);

	//读取数据存档数据
	if(ADemoGameStateBase *StateBase = GetWorld()->GetGameState<ADemoGameStateBase>())
	{
		if(ADemoGameStateBase::bIsNewGame == false)
		{
			StateBase->LoadPlayData();
		}
	}

	UpdateHealth(GetAttributeSet()->GetHealth() / GetAttributeSet()->GetMaxHealth());
	UpdateMana(GetAttributeSet()->GetMana() / GetAttributeSet()->GetMaxMana());
	UpdateStamina(GetAttributeSet()->GetStamina() / GetAttributeSet()->GetMaxStamina());
	UpdateExp(GetAttributeSet()->GetExp() / GetAttributeSet()->GetMaxExp());
	UpdateLevel(GetAttributeSet()->GetLevel());
}

void ADemoPlayerCharacter::ControlBackPack()
{
	if(GetWorld())
	{
		ADemoHUD *HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ADemoHUD>();
		if(HUD)
		{
			HUD->GetGameMainUI()->ShowAndHideBackPack();
		}
	}
}

void ADemoPlayerCharacter::ControlAttributePanel()
{
	if(GetWorld())
	{
		ADemoHUD *HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ADemoHUD>();
		if(HUD)
		{
			HUD->GetGameMainUI()->ShowAndHideAttributePanel();
		}
	}
}

void ADemoPlayerCharacter::ControlSaveAndLoadPanel()
{
	if(GetWorld())
	{
		ADemoHUD *HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ADemoHUD>();
		if(HUD)
		{
			HUD->GetGameMainUI()->ShowAndHideSaveAndLoadPanel();
		}
	}
}
