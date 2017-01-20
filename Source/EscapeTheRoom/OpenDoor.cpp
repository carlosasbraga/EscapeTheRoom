// Copyright Carlos Braga 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"


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

	// Initializes ActorThatSpawns as the DefaultPawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// local variables
	float Timer = 0.f; // timer for the door closing

	// Once PressurePlate overlaps with ActorThatOpens
	// rotate the owner of this component
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		OpenDoor();
		TimeDoorOpened = GetWorld()->GetTimeSeconds();
	}

	// Calculates time since the door opened
	// amd tests it to see if it is time to close it
	Timer = GetWorld()->GetTimeSeconds() - TimeDoorOpened;
	if (Timer >= TimeDoorCloses) 
	{
		CloseDoor();
	}
}

// opens the door
void UOpenDoor::OpenDoor()
{
	// Sets the yaw of the ObjectOwner to OpenAngle
	ObjectOwner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() 
{
	// Sets the yaw of the ObjectOwner to 0
	ObjectOwner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

