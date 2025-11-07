#include "AVRPBuildableMegaprojectStarter.h"
#include "FGActorRepresentationManager.h"

AAVRPBuildableMegaprojectStarter::AAVRPBuildableMegaprojectStarter()
{
	previewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondStorageInventory"));
}

void AAVRPBuildableMegaprojectStarter::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	RemoveAsRepresentation();
}

void AAVRPBuildableMegaprojectStarter::SetupStarter(TSubclassOf<AFGBuildable> megaproject, UStaticMesh* mesh, FTransform transform, bool display)
{
	cachedMegaproject = megaproject;

	previewMesh->SetStaticMesh(mesh);
	for (auto i = 0; i < previewMesh->GetNumMaterials(); i++) {
		previewMesh->SetMaterial(i, hologramMaterial);
	}

	previewMesh->SetWorldTransform(transform);

	SetDisplayPreviewPref(DisplayPreviewPref);
	SetToRepresent(display);
}

void AAVRPBuildableMegaprojectStarter::InitiateMegaproject()
{
	OnInitiationRequested.Broadcast();
}

void AAVRPBuildableMegaprojectStarter::SetToRepresent(bool display)
{
	Display |= display;
	UpdateRepresentation();
}

void AAVRPBuildableMegaprojectStarter::SetToRepresentPref(bool display)
{
	DisplayPref = display;
	UpdateRepresentation();
}

void AAVRPBuildableMegaprojectStarter::SetDisplayPreviewPref(bool display)
{
	DisplayPreviewPref = display;
	previewMesh->SetVisibility(DisplayPreviewPref);
}

bool AAVRPBuildableMegaprojectStarter::AddAsRepresentation()
{
	//Can also provide CreateAndAddNewRepresentation with custom UFGActorRepresentation class for advanced display on the map
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		cachedRepresentation = manager->CreateAndAddNewRepresentation(this);
		return true;
	}
	return false;
}

bool AAVRPBuildableMegaprojectStarter::UpdateRepresentation()
{
	//Call whenever you need to update what is displayed on the map for your building. For that call UpdateRepresentation
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		if ((!Display || !DisplayPref) && IsValid(cachedRepresentation)) {
			RemoveAsRepresentation();
		}
		else if (Display && DisplayPref && !IsValid(cachedRepresentation)) {
			AddAsRepresentation();
		}
		if (IsValid(cachedRepresentation)) manager->UpdateRepresentation(cachedRepresentation);
		return true;
	}
	return false;
}

bool AAVRPBuildableMegaprojectStarter::RemoveAsRepresentation()
{
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->RemoveRepresentation(cachedRepresentation);
		return true;
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
	return Cast<IAVRPMegaprojectInterface>(cachedMegaproject->GetDefaultObject())->GetActorRepresentationTexture();
}

UMaterialInterface* AAVRPBuildableMegaprojectStarter::GetActorRepresentationCompassMaterial()
{
	return Cast<IAVRPMegaprojectInterface>(cachedMegaproject->GetDefaultObject())->GetActorRepresentationCompassMaterial();
}

FText AAVRPBuildableMegaprojectStarter::GetActorRepresentationText()
{
	return FText::FromString(FString::Format(TEXT("{0}: {1}"), { mDisplayName.ToString(), cachedMegaproject.GetDefaultObject()->mDisplayName.ToString()}));
}

void AAVRPBuildableMegaprojectStarter::SetActorRepresentationText(const FText& newText){}

FLinearColor AAVRPBuildableMegaprojectStarter::GetActorRepresentationColor()
{
	//Only affects texture of icon in compass, just use this color for authenticity
	return FLinearColor(.1f, .1f, .1f);
}

void AAVRPBuildableMegaprojectStarter::SetActorRepresentationColor(FLinearColor newColor){}

ERepresentationType AAVRPBuildableMegaprojectStarter::GetActorRepresentationType()
{
	//This is a category the building will be displayed in, they are hardcoded. RT_SpaceElevator is an "Other" category (HUB, Space Elevator)
	return ERepresentationType::RT_SpaceElevator;
}

bool AAVRPBuildableMegaprojectStarter::GetActorShouldShowInCompass()
{
	//Does nothing
	return Display;
}

bool AAVRPBuildableMegaprojectStarter::GetActorShouldShowOnMap()
{
	//Does nothing
	return Display;
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

void AAVRPBuildableMegaprojectStarter::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance){}

TArray<FLocalUserNetIdBundle> AAVRPBuildableMegaprojectStarter::GetLastEditedBy() const
{
	//Can do nothing
	return TArray<FLocalUserNetIdBundle>();
}

void AAVRPBuildableMegaprojectStarter::SetActorLastEditedBy(const TArray<FLocalUserNetIdBundle>& LastEditedBy)
{
	//Can do nothing
}
