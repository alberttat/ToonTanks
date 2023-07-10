#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

private:
	class ATank *tankRef;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float fireRange = 700.f;
	FTimerHandle FireRateTimerHandle;
	float fireRate = 2.f;
	void CheckFireCondition();
	bool InFireRange();
};
