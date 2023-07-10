#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"

void ATank::BeginPlay()
{
    Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
}
ATank::ATank()
{
    tankSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
    tankSpringArm->SetupAttachment(RootComponent);
    tankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    tankCamera->SetupAttachment(tankSpringArm);
}
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FHitResult hitResult;
    if (TankPlayerController)
    {
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
        DrawDebugSphere(GetWorld(),
                        hitResult.ImpactPoint,
                        25.f,
                        12,
                        FColor::Red,
                        false,
                        -1.f);
        RotateTurret(hitResult.ImpactPoint);
    }
}
void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

void ATank::Move(float value)
{
    float DeltaTime;
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = value * DeltaTime * speed;
    AddActorLocalOffset(DeltaLocation, true);
    // UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
    GetController();
}
void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = value * DeltaTime * turnRate;
    AddActorLocalRotation(DeltaRotation, true);
}
