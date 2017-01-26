// Copyright Carlos Braga 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get the owner 
	ObjectOwner = GetOwner();
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Protect PressurePlate pointer
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("PressurePlate not found. nullptr reference."))
	}

}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Once PressurePlate overlaps with ActorThatOpens
	// broadcast the open event
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) 
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	// Escape the function if PressurePlate is a nullptr
	if (!PressurePlate) 
	{ 
		return 0.f; 
	}

	// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (const auto& DisposableActor : OverlappingActors)
	{
		TotalMass += DisposableActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

