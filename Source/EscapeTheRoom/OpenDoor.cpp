// Copyright Carlos Braga 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get the owner and store it in ObjectOwner
	AActor* ObjectOwner = GetOwner();
	
	// prints the name of the ObjectOwner to the console
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectOwner->GetName());

	ObjectOwner->AddActorWorldRotation(FRotator(0.0f, -10.0f, 0.0f).Quaternion());
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

