#include "AVRPBuildableMegaprojectStarter.h"
#include "FGActorRepresentationInterface.h"
#include "FGActorRepresentationManager.h"
#include "UnrealNetwork.h"

AAVRPBuildableMegaprojectStarter::AAVRPBuildableMegaprojectStarter()
{
	previewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondStorageInventory"));
}

void AAVRPBuildableMegaprojectStarter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAVRPBuildableMegaprojectStarter, Display);
	DOREPLIFETIME(AAVRPBuildableMegaprojectStarter, cachedMegaproject);
	DOREPLIFETIME(AAVRPBuildableMegaprojectStarter, MegaprojectLocation);
	DOREPLIFETIME(AAVRPBuildableMegaprojectStarter, MegaprojectMesh);
}

void AAVRPBuildableMegaprojectStarter::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	RemoveAsRepresentation();
}

void AAVRPBuildableMegaprojectStarter::SetupStarter(TSubclassOf<AFGBuildable> megaproject, UStaticMesh* mesh, FTransform transform, bool display)
{
	cachedMegaproject = megaproject;

	MegaprojectMesh = mesh;
	OnRep_MegaprojectMesh();

	MegaprojectLocation = transform;
	OnRep_MegaprojectLocation();

	SetDisplayPreviewPref(DisplayPreviewPref);
	SetToRepresent(display);
}

void AAVRPBuildableMegaprojectStarter::InitiateMegaproject()
{
	OnInitiationRequested.ExecuteIfBound();
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

void AAVRPBuildableMegaprojectStarter::OnRep_Display()
{
	UpdateRepresentation();
}

void AAVRPBuildableMegaprojectStarter::OnRep_MegaprojectLocation()
{
	previewMesh->SetWorldTransform(MegaprojectLocation);
}

void AAVRPBuildableMegaprojectStarter::OnRep_MegaprojectMesh()
{
	previewMesh->SetStaticMesh(MegaprojectMesh);
	for (auto i = 0; i < previewMesh->GetNumMaterials(); i++) {
		previewMesh->SetMaterial(i, hologramMaterial);
	}
}

bool AAVRPBuildableMegaprojectStarter::AddAsRepresentation()
{
	//Can also provide CreateAndAddNewRepresentation with custom UFGActorRepresentation class for advanced display on the map
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		cachedRepresentation = manager->CreateAndAddNewRepresentation(this, true);
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
		manager->RemoveRepresentationOfActor(this);
		cachedRepresentation = nullptr;
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
	return Cast<IFGActorRepresentationInterface>(cachedMegaproject->GetDefaultObject())->GetActorRepresentationTexture();
}

UMaterialInterface* AAVRPBuildableMegaprojectStarter::GetActorRepresentationCompassMaterial()
{
	return Cast<IFGActorRepresentationInterface>(cachedMegaproject->GetDefaultObject())->GetActorRepresentationCompassMaterial();
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
	//Behaviour may be unpredictable, so I'd advice to instead show/hide icon by creating/removing representations 
	return Display;
}

bool AAVRPBuildableMegaprojectStarter::GetActorShouldShowOnMap()
{
	//Behaviour may be unpredictable, so I'd advice to instead show/hide icon by creating/removing representations 
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
