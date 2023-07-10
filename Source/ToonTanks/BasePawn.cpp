#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collisder"));
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}
void ABasePawn::HandleDestruction()
{
	// visual/sound effects
	if (DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathEffect,
			GetActorLocation(),
			GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}
void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(),
						 LookAtRotation,
						 UGameplayStatics::GetWorldDeltaSeconds(this),
						 5.f));
}

void ABasePawn::Fire()
{
	DrawDebugSphere(GetWorld(),
					ProjectileSpawnPoint->GetComponentLocation(),
					25.f,
					12,
					FColor::Red,
					false,
					3.f);

	auto Projectile = GetWorld()
						  ->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}
