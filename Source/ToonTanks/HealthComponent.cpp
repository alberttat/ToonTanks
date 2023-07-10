#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = MaxHealth;
	// Projectile->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	if (Damage <= 0)
		return;
	CurrentHealth -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), CurrentHealth);
	if (CurrentHealth <= 0.f)
	{
		if (ToonTanksGameMode)
		{
			ToonTanksGameMode->ActorDied(DamagedActor);
		}
	}
}
