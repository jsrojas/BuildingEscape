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
	TargetYaw = InitialYaw + TargetYaw;

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
	// Printing the three elements of rotation (Roll, Pitch, Yaw) to see how it moves
	//UE_LOG(LogTemp, Warning, TEXT("The rotation is: %s"), *GetOwner()->GetActorRotation().ToString());

	// Printing how Yaw changes since is the one rotating the door to open it
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 0.8f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	// FIRST EXAMPLE ABOUT HOW TO OPEN THE DOOR------------------------------------------------------------------------
	// Obtaining the current Yaw value of the Actor (the door)
	//float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// Creating an FRotator to rotate the door
	//FRotator OpenDoor(0.f, TargetYaw, 0.f);
	// Setting the new Yaw value with exponential interpolation - this one is dependant of the frame rate of the pc
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.05f);
	// Setting the new Yaw value with an actual linear interpolation
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45);
	// Another way to set the new Yaw value with linear interpolation
	//OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	// Opening the door with the desired coordinates
	//GetOwner()->SetActorRotation(OpenDoor);
	//-----------------------------------------------------------------------------------------------------------------
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * 2.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
