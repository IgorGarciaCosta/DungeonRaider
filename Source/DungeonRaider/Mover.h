// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.generated.h"

UCLASS()
class DUNGEONRAIDER_API AMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		FVector MoveOffset;

	UPROPERTY(EditAnywhere)
		float MoveTime = 4;

	UPROPERTY(EditAnywhere)
		bool ShouldMove = true;

	FVector OriginalLoc;

};
