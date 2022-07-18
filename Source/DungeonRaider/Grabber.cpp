// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	/*UPhysicsHandleComponent* PhysicsHadle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHadle != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("PhysicsHadle: %s"), *PhysicsHadle->GetName());
		PhysicsHadle->GetName();
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No PH found"));
	}*/
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHadle = GetPhysicsHandle();
	
	if (PhysicsHadle && PhysicsHadle->GetGrabbedComponent()) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHadle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

	}

	//FRotator MyRot = GetComponentRotation();
	//FString RotString = MyRot.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Rot: %s"), *RotString);

	//UWorld* World = GetWorld();
	//float Time = GetWorld()->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("Current time: %f"), Time);

	//// ...
	
	
}

void UGrabber::Release()
{
	
	UPhysicsHandleComponent* MyPhysicsHandle = GetPhysicsHandle();
	if (MyPhysicsHandle == nullptr) return;

	if (MyPhysicsHandle->GetGrabbedComponent() != nullptr) {
		MyPhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		

		AActor* GrabbedActor =MyPhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");

		MyPhysicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Display, TEXT("released"));
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHadle = GetPhysicsHandle();
	if (PhysicsHadle == nullptr) return;

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		PhysicsHadle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
		//UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *HitResult.GetActor()->GetActorNameOrLabel());
		/*DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Blue, false, 5.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5.f);

		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *HitActor->GetActorNameOrLabel());*/
	}
	else { 
		UE_LOG(LogTemp, Display, TEXT("NOTHING")); 
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false);


	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->SweepSingleByChannel(OutHitResult,
		Start,
		End,
		FQuat::Identity, ECollisionChannel::ECC_WorldDynamic,
		Sphere,
		Params
	);
}



UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) {
		UE_LOG(LogTemp, Display, TEXT("NO PHC IN GRABBER"));

	}
	return Result;
}

