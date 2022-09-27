// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Sword.h"
#include "Gun.h"
#include "HealthComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "Checkpoint.h"
#include "AdventureTimeGameModeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//These stuff will change if I change mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	
	Sword = GetWorld()->SpawnActor<ASword>(SwordClass);
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponsocket"));
	Sword->SetOwner(this);
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponsocket"));
	Gun->SetOwner(this);

	Gun->SetHidden(true);
	CurrentWeapon = 0;

	QuestActivated = true;

	// Load game.
	 UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	 if ((GameInstance != nullptr) && (GameInstance->LoadGame()))
	 {
	 	if (GameInstance->CurrentSaveGame != nullptr)
	 	{
	 		// Retrieve the req saved data
	 		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	 		PlayerPawn->SetActorLocation(GameInstance->CurrentSaveGame->SaveLocation);
	 		/*QuestList = GameInstance->CurrentSaveGame->QuestStatus;*/
	 	}
	 }

	 CharacterName = TEXT("Player");//hardcoding for now
}

void APlayerCharacter::UpdateAndShowQuestList()
{
	// Prepare list of quest, to show on the UI
	AAdventureTimeGameModeBase* GameMode = Cast<AAdventureTimeGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode != nullptr)
	{
		TArray<FText> QuestTextList;
		for (int i = 0; i < QuestList.Num(); i++)
		{
			if (!QuestList[i].IsCompleted)
			{
				bool Success = false;
				// Find the quest on the game mode
				FQuest Quest = GameMode->FindQuest(QuestList[i].QuestID, Success);

				if (Success)
				{
					QuestTextList.Add(Quest.SortDescription);
				}
			}
		}

		OnShowUpdatedQuestList(QuestTextList);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SwitchWeapon);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	//PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SaveGame);
	//PlayerInputComponent->BindAction(TEXT("InterectNPC"), EInputEvent::IE_Pressed, this, &APlayerCharacter::InterectNPC);
	//PlayerInputComponent->BindAction(TEXT("HideUItesting"), EInputEvent::IE_Pressed, this, &APlayerCharacter::HideUi);

}



void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
	/* Question: is this really frame rate independent and no need to mult by delta time??*/
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}


void APlayerCharacter::SwitchWeapon()
{
	CurrentWeapon++;
	if (CurrentWeapon % 2 == 0)
	{
		Gun->SetHidden(true);
		Sword-> SetHidden(false);
	}
	else 
	{
		Gun->SetHidden(false);
		Sword-> SetHidden(true);
	}
}

void APlayerCharacter::SaveGame()
{
		// Save current game
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if ((GameInstance != nullptr) && (GameInstance->CurrentSaveGame != nullptr))
		{
			//TODO: Save currentlocation in savelocation.
			APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			GameInstance->CurrentSaveGame->SaveLocation = PlayerPawn->GetActorLocation();
			//GameInstance->CurrentSaveGame->QuestStatus.Empty();
			//GameInstance->CurrentSaveGame->QuestStatus = QuestList;

			if (GameInstance->SaveGame())
			{
				UE_LOG(LogTemp, Warning, TEXT("Success saving game (Playerchar)"));

				return;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Fail saving game (Playerchar)"));
	
}

void APlayerCharacter::InterectNPC()
{	
	OnInteract_Implementation();
}

float APlayerCharacter::GetSliceAnimationPosition()
{
	return GetMesh()->GetAnimInstance()->Montage_GetPosition(Slice);
}

void APlayerCharacter::Attack()
{
	if (Slice && CurrentWeapon % 2 == 0)
	{	
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(Slice) == false) {//to stop player from running code when already attacking.
			//GetMesh()->SetAnimation(Slice);
			//GetMesh()->PlayAnimation(Slice, false);
			PlayAnimMontage(Slice);
		}
	}
	else
	{
		//TODO: put animation
		Gun->Fire();
	}
}

void APlayerCharacter::TakeDamage()
{
	if (TakingDamage)
	{
		GetMesh()->SetAnimation(TakingDamage);
		GetMesh()->PlayAnimation(TakingDamage, false);
	}
}

void APlayerCharacter::Test()
{
	SaveGame();
}

bool APlayerCharacter::FindQuest(FName QuestID, FQuestItem& Quest)
{
	for (int i = 0; i < QuestList.Num(); i++)
	{
		if (QuestList[i].QuestID == QuestID)
		{
			Quest = QuestList[i];
			return true;
		}
	}
	return false;
}

void APlayerCharacter::AcceptQuest(FName QuestID)
{
	bool QuestFound = false;
	for (int i = 0; i < QuestList.Num(); i++)
	{
		if (QuestList[i].QuestID == QuestID)
		{
			QuestFound = true;
			break;
		}
	}

	if (!QuestFound)
	{
		FQuestItem NewQuest;
		NewQuest.QuestID = QuestID;
		NewQuest.IsCompleted = false;
		QuestList.Add(NewQuest);

		UpdateAndShowQuestList();
	}

}

void APlayerCharacter::MarkQuestCompleted(FName QuestID)
{
	for (int i = 0; i < QuestList.Num(); i++)
	{
		if ((QuestList[i].QuestID == QuestID) && (!QuestList[i].IsCompleted))
		{
			QuestList[i].IsCompleted = true;
			break;
		}
	}

	UpdateAndShowQuestList();
}


//for testing
void APlayerCharacter::OnInteract_Implementation()
{
	OnShowUI(CharacterName);

	// Retrieve info quest from game mode
	AAdventureTimeGameModeBase* GameMode = Cast<AAdventureTimeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr) return;

	if (!QuestActivated) return;
	
	bool Success = false;
	// Find the quest on the game mode
	FQuest Quest = GameMode->FindQuest(QuestId, Success);

	if (!Success) return;
	

	// Check if player has already accepted the quest
	bool bQuestAccepted = false;
	FQuestItem QuestInfo;
	bQuestAccepted = FindQuest(QuestId, QuestInfo);

	// Quest not accepted, show info quest mark quest as a accepted
	if (!bQuestAccepted)
	{
		UE_LOG(LogTemp, Warning, TEXT("got u!"));

		OnShowQuestInfo(Quest);
		AcceptQuest(QuestId);
	}
}


void APlayerCharacter::HideUi()
{
	OnHideUI();
}