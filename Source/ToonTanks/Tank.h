#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
	APlayerController *GetTankPlayerController() const { return TankPlayerController; }
	bool bAlive = true;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent *tankSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent *tankCamera;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 400;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 25;
	void Move(float value);
	void Turn(float value);
	APlayerController *TankPlayerController;
};
