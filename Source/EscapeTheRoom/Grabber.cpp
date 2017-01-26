// Copyright Carlos Braga 2017

#include "EscapeTheRoom.h"
#include "Grabber.h"

#define OUT // Just to say the parameters are out parameters in a function call

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get direction the player is looking at
	FVector LineTraceEnd = GetDirectionPlayerIsLookingAt();

	// Escape the function if the Physics Handle is a nullptr
	if (!PhysicsHandle) { return; }

	// If the Physics Handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// Move object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	// Line-trace and see if we reach any actors with physics collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	// If we hit, grab the Actor 
	if (ActorHit) 
	{
		// Escape the function if the Physics Handle is a nullptr
		if (!PhysicsHandle) { return; }

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

// Release Physics handle
void UGrabber::Release()
{
	// Escape the function if the Physics Handle is a nullptr
	if (!PhysicsHandle) { return; }

	PhysicsHandle->ReleaseComponent();
}

// Look for attached Physics Handle Component
void UGrabber::FindPhysicsComponent()
{
	// Local variables
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Report on failure to find the Physics Handle Component
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found in Actor %s."), *GetOwner()->GetName())
	}
}

// Look for attached Input Components
void UGrabber::SetupInputComponent()
{
	// Local variables
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	// Report on failure to find the Input Component or binds the input action
	if (PawnInput)
	{
		// Bind the input action
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Release", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		// Failure
		UE_LOG(LogTemp, Error, TEXT("Input Component not found in Actor %s."), *GetOwner()->GetName())
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get direction the player is looking at
	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector LineTraceEnd = GetDirectionPlayerIsLookingAt();

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line-Trace (AKA ray-cast) to Reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerPosition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

FVector UGrabber::GetDirectionPlayerIsLookingAt()
{
	// Get player viewpoint
	FRotator PlayerRotator; // The position of the player relative to the world
	FVector PlayerPosition; // The direction the player is looking in the world

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerPosition,
		OUT PlayerRotator
	);

	return PlayerPosition + Reach * PlayerRotator.Vector();
}