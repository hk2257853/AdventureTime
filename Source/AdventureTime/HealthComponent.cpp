// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AdventureTimeGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	health = defaultHealth;
	gameModeRef = Cast<AAdventureTimeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser)
{
	if (damage == 0 || health <= 0) { return; }
	health = FMath::Clamp(health - damage, 0.f, defaultHealth);
	if (health <= 0) {
		if (gameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("ACTOR DEAD!!!!"));

			//gameModeRef->ActorDied(GetOwner()); TODO: just play death animation and record enemy died in data table?
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No valid game mode reference"));
		}
	}
}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

