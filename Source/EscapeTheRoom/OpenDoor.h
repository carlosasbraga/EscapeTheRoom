// Copyright Carlos Braga 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Methods
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Properties
	// Event for opening the doors
	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnOpenRequest;

	// Event for opening the doors
	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnCloseRequest;

private:
	// Properties
	// The pressure plate
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	// The owner of this component
	AActor* ObjectOwner = nullptr;

	// The mass necessary to opend doors
	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.f;

	// Methods

	// Closes the door
	void CloseDoor();

	float GetTotalMassOfActorsOnPlate();
};
