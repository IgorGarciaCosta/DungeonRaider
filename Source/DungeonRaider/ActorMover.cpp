// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMover.h"
#include "Math/UnrealMathUtility.h"



// Sets default values for this component's properties
UActorMover::UActorMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
	// ...
	
	
}


// Called every frame
void UActorMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector TargetLocation = OriginalLocation;

	if (ShouldMove)
	{
		//UE_LOG(LogTemp, Display, TEXT("Should"));
		TargetLocation = OriginalLocation + MoveOffset;
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FString loc = TargetLocation.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Loc: %s"), *loc);
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
	//else UE_LOG(LogTemp, Display, TEXT("Nop"));

	// ...
}

void UActorMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

