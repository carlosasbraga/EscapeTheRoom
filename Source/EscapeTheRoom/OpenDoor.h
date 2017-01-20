// Copyright Carlos Braga 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Properties
	// Angle to rotate the door
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	// The pressure plate
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	// The owner of this component
	AActor* ObjectOwner;

	// The AActor that can interact with PressurePlate
	AActor* ActorThatOpens;

	// The instant the door opened
	float TimeDoorOpened;

	// Time the door closes
	UPROPERTY(EditAnywhere)
	float TimeDoorCloses = 1.f;

	// Methods
	// Opens the door
	void OpenDoor();

	// Closes the door
	void CloseDoor();
};
