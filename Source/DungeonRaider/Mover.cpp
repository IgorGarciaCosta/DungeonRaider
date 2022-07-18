// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMover::AMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLoc = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Test");
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ShouldMove) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Test");
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = OriginalLoc + MoveOffset;
		float Speed = FVector::Distance(OriginalLoc, TargetLocation) / MoveTime;
		FVector NewLoc = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		SetActorLocation(NewLoc);
	}
	

}

