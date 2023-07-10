#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (InFireRange())
    {
        RotateTurret(tankRef->GetActorLocation());
    }
}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
void ATower::BeginPlay()
{
    Super::BeginPlay();
    tankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, fireRate, 1);
}

void ATower::CheckFireCondition()
{
    if (tankRef)
    {

        if (InFireRange() && (tankRef->bAlive == true))
        {
            RotateTurret(tankRef->GetActorLocation());
            Fire();
        }
    }
}

bool ATower::InFireRange()
{
    if (tankRef)
    {
        float distance = FVector::Dist(
            GetActorLocation(),
            tankRef->GetActorLocation());
        if (distance <= fireRange)
        {
            return true;
        }
    }
    return false;
}