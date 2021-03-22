// Copyright Juan Sebastian Rojas Melendez 2021

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle = InitialYaw + OpenAngle;

	if (!PressurePlate)
	{
		FString ActorName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("The actor %s has the door component on it, but does not have the Pressure Plate set"), *ActorName);
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		// Store the time instant that the door was opened
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		// If the door has been open longer than DoorCloseDelay then close the door
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorClosedDelay) 
		//if (GetWorld()->GetTimeSeconds() > (DoorLastOpened + DoorClosedDelay))
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// OPENING THE DOOR
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	// FIRST EXAMPLE ABOUT HOW TO OPEN THE DOOR------------------------------------------------------------------------
	// Obtaining the current Yaw value of the Actor (the door)
	//float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// Creating an FRotator to rotate the door
	//FRotator OpenDoor(0.f, OpenAngle, 0.f);
	// Setting the new Yaw value with exponential interpolation - this one is dependant of the frame rate of the pc
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, OpenAngle, 0.05f);
	// Setting the new Yaw value with an actual linear interpolation
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 45);
	// Another way to set the new Yaw value with linear interpolation
	//OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, 2);
	// Opening the door with the desired coordinates
	//GetOwner()->SetActorRotation(OpenDoor);
	//-----------------------------------------------------------------------------------------------------------------
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorClosingSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
