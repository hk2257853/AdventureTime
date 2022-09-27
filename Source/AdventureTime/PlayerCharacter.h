// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AdventureTime/Definition.h" 
#include "PlayerCharacter.generated.h"


class ASword;
class AGun;
class UHealthComponent;
class AEnemyCharacter;

UCLASS()
class ADVENTURETIME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//on sword hit just for testing if sword works
	void TakeDamage();
	void Test();

	bool FindQuest(FName QuestID, FQuestItem& Quest);
	void AcceptQuest(FName QuestID);
	void MarkQuestCompleted(FName QuestID);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnShowQuestInfo(FQuest Quest);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnShowQuestCompleted(const FText& Message);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnShowUpdatedQuestList(const TArray<FText>& QuestTextList);
	

	//new stuff. see if works after this
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnShowUI(FName Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnHideUI(); //call this on overlap end later
	
	FName CharacterName;

	void SaveGame();
	void InterectNPC();
	void HideUi();

	float GetSliceAnimationPosition();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FQuestItem> QuestList;

	void UpdateAndShowQuestList();
	//for testing:
	void OnInteract_Implementation();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cat")
		FName QuestId;

	bool QuestActivated = false;


private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Attack();
	void SwitchWeapon();

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* Slice;

	//UPROPERTY(EditAnywhere, Category = "Animation")
	//	UAnimationAsset* ShootAnim;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimationAsset* TakingDamage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASword> SwordClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	ASword* Sword;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY()
	int32 CurrentWeapon = 0;  //even-sowrd. odd-gun

	AEnemyCharacter* enemy;

	class ACheckpoint* Checkpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

};
