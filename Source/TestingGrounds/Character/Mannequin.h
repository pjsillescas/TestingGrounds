// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCamera;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FPArms;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	class AGun* Gun;

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TSubclassOf<class AGun> BlueprintGunClass;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable,Category = "Weapon")
	void Fire();
};
