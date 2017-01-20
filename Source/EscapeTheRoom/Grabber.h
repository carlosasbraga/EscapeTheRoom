// Copyright Carlos Braga 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Public methods
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	//Private members
	// Distance the player can reach in cm
	float Reach = 100.f;

	// Components attached to DefaultPawn
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* PawnInput = nullptr;

	// Private Method
	// Ray-cast and grab what is reacheable
	void Grab();

	// Release the Actor grabbed
	void Release();

	// Find attached Physics Handle Component
	void FindPhysicsComponent();

	// Setup attached Input Component
	void SetupInputComponent();

	// Return hit for the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Return vector with the direction the layer is looking at 
	FVector GetDirectionPlayerIsLookingAt();
};