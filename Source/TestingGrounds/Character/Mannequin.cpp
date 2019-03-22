// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"

#include "Components/ChildActorComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(RootComponent);
	FPCamera->SetRelativeLocation(FVector(-39.56,1.75,64));
	FPCamera->SetRelativeRotation(FQuat(FRotator(0, 0, 0)));
	FPCamera->bUsePawnControlRotation = true;


	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetupAttachment(FPCamera);
	FPArms->SetRelativeLocation(FVector(-0.5,-4.4,-155.7));
	FPArms->SetRelativeRotation(FQuat(FRotator(1.9, -19.19, 5.2)));
	FPArms->SetOnlyOwnerSee(true);
	FPArms->bCastDynamicShadow = false;
	FPArms->CastShadow = false;
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	if(BlueprintGunClass == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Gun blueprintMissing"));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(BlueprintGunClass);
	Gun->AttachToComponent(FPArms,FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),TEXT("GripPoint"));
	Gun->AnimInstance = FPArms->GetAnimInstance();
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::Fire()
{
	Gun->Fire();
}
