#include "AVRPBuildableMegaprojectStarter.h"
#include "FGActorRepresentationManager.h"

void AAVRPBuildableMegaprojectStarter::SetDisplayLocation(bool display)
{
	Display = display;
	//manipulate actor representation interface
}

void AAVRPBuildableMegaprojectStarter::InitiateMegaproject()
{
	OnInitiationRequested.Broadcast();
}

bool AAVRPBuildableMegaprojectStarter::AddAsRepresentation()
{
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->CreateAndAddNewRepresentation(this);
		return true;
	}
	return false;
}

bool AAVRPBuildableMegaprojectStarter::UpdateRepresentation()
{
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->UpdateRepresentationOfActor(this);
		return true;
	}
	return false;
}

bool AAVRPBuildableMegaprojectStarter::RemoveAsRepresentation()
{
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		return manager->RemoveRepresentationOfActor(this);
	}
	return false;
}

bool AAVRPBuildableMegaprojectStarter::IsActorStatic()
{
	return true;
}

FVector AAVRPBuildableMegaprojectStarter::GetRealActorLocation()
{
	return GetActorLocation();
}

FRotator AAVRPBuildableMegaprojectStarter::GetRealActorRotation()
{
	return GetActorRotation();
}

UTexture2D* AAVRPBuildableMegaprojectStarter::GetActorRepresentationTexture()
{
	return nullptr;
}

UMaterialInterface* AAVRPBuildableMegaprojectStarter::GetActorRepresentationCompassMaterial()
{
	return nullptr;
}

FText AAVRPBuildableMegaprojectStarter::GetActorRepresentationText()
{
	return mDisplayName;
}

void AAVRPBuildableMegaprojectStarter::SetActorRepresentationText(const FText& newText)
{
	//This seems like a thing for nameable stuff, don't need to implement
}

FLinearColor AAVRPBuildableMegaprojectStarter::GetActorRepresentationColor()
{
	return FLinearColor();
}

void AAVRPBuildableMegaprojectStarter::SetActorRepresentationColor(FLinearColor newColor)
{
}

ERepresentationType AAVRPBuildableMegaprojectStarter::GetActorRepresentationType()
{
	return ERepresentationType::RT_SpaceElevator;
}

bool AAVRPBuildableMegaprojectStarter::GetActorShouldShowInCompass()
{
	return true;
}

bool AAVRPBuildableMegaprojectStarter::GetActorShouldShowOnMap()
{
	return true;
}

EFogOfWarRevealType AAVRPBuildableMegaprojectStarter::GetActorFogOfWarRevealType()
{
	return EFogOfWarRevealType::FOWRT_None;
}

float AAVRPBuildableMegaprojectStarter::GetActorFogOfWarRevealRadius()
{
	return 0.0f;
}

ECompassViewDistance AAVRPBuildableMegaprojectStarter::GetActorCompassViewDistance()
{
	return ECompassViewDistance::CVD_Far;
}

void AAVRPBuildableMegaprojectStarter::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance)
{
}

TArray<FLocalUserNetIdBundle> AAVRPBuildableMegaprojectStarter::GetLastEditedBy() const
{
	//No idea what do I need that for
	return TArray<FLocalUserNetIdBundle>();
}

void AAVRPBuildableMegaprojectStarter::SetActorLastEditedBy(const TArray<FLocalUserNetIdBundle>& LastEditedBy)
{
}
