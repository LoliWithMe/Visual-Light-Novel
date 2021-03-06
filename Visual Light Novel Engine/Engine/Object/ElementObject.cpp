#include "../../stdafx.h"
#include "ElementObject.h"
#include "../EngineIO.h"
#include <fstream>
#include <iomanip>
#include "../../Core/Util.h"
#include "../Blueprint/Blueprint.h"


ElementObject::ElementObject(string window, string elementPath, string shaderPath)
	: element(nullptr)
	, shader(nullptr)
{
	EngineIO::LoadElement(elementPath, &element);

	if (!element)
	{
		MessageBox(NULL, "������Ʈ ������ �ƴմϴ�!", "������Ʈ ����!", MB_OK | MB_ICONERROR);
		return;
	}

	for (auto path : element->StateImage)
	{
		Texture2D * tex = RESOURCES->GetResource<Texture2D>(path.second, window);
		textures.insert(make_pair(path.first, tex));
	}

	stateName = textures.begin()->first;

	shader = RESOURCES->GetResource<Shader>(shaderPath, window);
	this->window = window;
	this->shaderPath = shaderPath;
	this->elementPath = elementPath;

	context = GRAPHICS->GetDeviceContext(window);

	CreateBuffers();
}

ElementObject::~ElementObject()
{
	SAFE_DELETE(shader);
}

void ElementObject::Update()
{
	Drag();
}

void ElementObject::Render()
{
	CAMERA->Render();
	RenderBuffers();

	for (auto tex : textures)
	{
		if (tex.first.compare(stateName) == 0)
		{
			shader->RenderShader
			(
				6,
				this,
				color,
				D3DXVECTOR4(tex.second->GetDesc().Width, tex.second->GetDesc().Height, scale.x, scale.y),
				tex.second->GetSRV(),
				window
			);
		}
	}
}

void ElementObject::ChangeShader(string shaderPath)
{
	SAFE_DELETE(shader);
	shader = RESOURCES->GetResource<Shader>(shaderPath, window);
}

void ElementObject::SetState(wstring state)
{
	stateName = state;
}

bool ElementObject::IsOver()
{
	RECT rc;
	rc.left = position.x + offset.x + vertexRect.left * scale.x;
	rc.right = position.x + offset.x + vertexRect.right * scale.x;
	rc.top = position.y + offset.y + -vertexRect.top * scale.y;
	rc.bottom = position.y + offset.y + -vertexRect.bottom * scale.y;

	if (PtInRect(&rc, INPUT->GetMousePos(window)) && IsFocus(window))
		return true;

	return false;
}

void ElementObject::Save()
{
	json data;
	data["ELEMENT"] = elementPath;
	data["SHADER"] = "Shaders/Texture2D.hlsl";

	bpList->Save(data);

	string fileName = Util::GetFileName(const_cast<char*>(elementPath.c_str()));

	ofstream stream("Project/Objects/" + fileName);
	stream << setw(2) << data << endl;
}

void ElementObject::Load(json & data)
{
}
