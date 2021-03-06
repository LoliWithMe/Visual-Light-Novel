#include "../../stdafx.h"
#include "BP_Object.h"
#include "../../Core/Util.h"
#include "../../Scenes/SC_Editor.h"
#include "../Object/Object.h"


BP_Object::BP_Object()
	: origObject(nullptr)
{
	type = BlueprintType::OBJECT;
	object2D->SetColor(D3DXVECTOR4(255 / 255.0f, 239 / 255.0f, 224 / 255.0f, 1));
}

BP_Object::BP_Object(GameObject * object)
{
	type = BlueprintType::OBJECT;
	object2D->SetColor(D3DXVECTOR4(255 / 255.0f, 239 / 255.0f, 224 / 255.0f, 1));

	objectData.Position = object->GetPosition() - object->GetOffset();
	objectData.Rotation = object->GetRotation();
	objectData.Scale = object->GetScale();
	objectData.Color = object->GetColor();

	origObject = object;
}

BP_Object::~BP_Object()
{
}

void BP_Object::Load(json & data)
{
	objectData.Color = Util::StringToVector4(data["DATA"]["VALUE"].value("COLOR", ""));
	objectData.Position = Util::StringToVector3(data["DATA"]["VALUE"].value("POSITION", ""));
	objectData.Rotation = Util::StringToVector3(data["DATA"]["VALUE"].value("ROTATION", ""));
	objectData.Scale = Util::StringToVector3(data["DATA"]["VALUE"].value("SCALE", ""));
}

void BP_Object::Save(json & data, int layer, int objIndex, int bpIndex)
{
	Blueprint::Save(data, layer, objIndex, bpIndex);
	THISPATHO(layer, objIndex, bpIndex)["DATA"]["VALUE"]["POSITION"] = Util::VectorToString(objectData.Position);
	THISPATHO(layer, objIndex, bpIndex)["DATA"]["VALUE"]["ROTATION"] = Util::VectorToString(objectData.Rotation);
	THISPATHO(layer, objIndex, bpIndex)["DATA"]["VALUE"]["SCALE"] = Util::VectorToString(objectData.Scale);
	THISPATHO(layer, objIndex, bpIndex)["DATA"]["VALUE"]["COLOR"] = Util::VectorToString(objectData.Color);
}

void BP_Object::Save(json & data, int objIndex, int bpIndex)
{
	Blueprint::Save(data, objIndex, bpIndex);
	THISPATHU(objIndex, bpIndex)["DATA"]["VALUE"]["POSITION"] = Util::VectorToString(objectData.Position);
	THISPATHU(objIndex, bpIndex)["DATA"]["VALUE"]["ROTATION"] = Util::VectorToString(objectData.Rotation);
	THISPATHU(objIndex, bpIndex)["DATA"]["VALUE"]["SCALE"] = Util::VectorToString(objectData.Scale);
	THISPATHU(objIndex, bpIndex)["DATA"]["VALUE"]["COLOR"] = Util::VectorToString(objectData.Color);
}

void BP_Object::Save(json & data, int bpIndex)
{
	Blueprint::Save(data, bpIndex);
	THISPATHE(bpIndex)["DATA"]["VALUE"]["POSITION"] = Util::VectorToString(objectData.Position);
	THISPATHE(bpIndex)["DATA"]["VALUE"]["ROTATION"] = Util::VectorToString(objectData.Rotation);
	THISPATHE(bpIndex)["DATA"]["VALUE"]["SCALE"] = Util::VectorToString(objectData.Scale);
	THISPATHE(bpIndex)["DATA"]["VALUE"]["COLOR"] = Util::VectorToString(objectData.Color);
}

void BP_Object::SubUpdate()
{
	WRITE->Text(L"Ŭ�� �� �̸�����", D3DXVECTOR2(object2D->GetPosition()), "Blueprint", 14, L"����������", D3DXCOLOR(0.5, 0.5, 0.5, 1));
}

void BP_Object::Preview()
{
	origObject->SetPosition(objectData.Position);
	origObject->SetRotation(objectData.Rotation);
	origObject->SetScale(objectData.Scale);
	origObject->SetColor(objectData.Color);
}
