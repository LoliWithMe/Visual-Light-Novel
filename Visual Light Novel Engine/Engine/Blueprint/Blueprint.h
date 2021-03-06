#pragma once
#include "../../Core/Components/GameObject.h"
#include "../../Core/Components/Sequence.h"
#include "../../Core/json.hpp"

#define THISPATHO(layer, objIndex, bpIndex) data["LAYER"][to_string(layer)]["OBJECT"][objIndex]["BLUEPRINT"]["LIST"][bpIndex]
#define THISPATHU(objIndex, bpIndex) data["UI"][objIndex]["BLUEPRINT"]["LIST"][bpIndex]
#define THISPATHE(bpIndex) data["BLUEPRINT"]["LIST"][bpIndex]

using namespace nlohmann;

class Blueprint;
class Object2D;

enum class BlueprintType
{
	FUNCTION,
	OBJECT,
	FLOAT,
	SEQUENCE,
	UI
};

enum class BlueprintSubType
{
	NONE,
	SEQUENCE_QUEUE_EASEIN,
	SEQUENCE_QUEUE_EASEOUT,
	SEQUENCE_QUEUE_EASEINOUT,
	SEQUENCE_QUEUE_LINEAR,
	SEQUENCE_QUEUE_BEZIER2,
	SEQUENCE_QUEUE_BEZIER3,
	UI_GAME_START,
	UI_GAME_END,
	UI_GAME_SAVE,
	UI_GAME_LOAD,
	UI_SCENE_TITLE,
	UI_SCENE_OPTION,
	UI_SCENE_CG,
	UI_SCENE_SELECT,
	UI_SCENE_DIALOGUE,
	UI_SCENE_SAVE
};

enum class BlueprintObjectType
{
	IMAGE,
	UIObject,
	ELEMENT
};

struct BlueprintObject
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
	D3DXVECTOR4 Color;
};

struct BlueprintSubData
{
	void * Data;
	BlueprintType Type;
};

struct BlueprintNode
{
	Blueprint * data;
	BlueprintNode * next;
	BlueprintNode * prev;
};

struct BlueprintLinkData
{
	UINT data;
	vector<UINT> subdata;
	UINT next;
	UINT prev;
};

namespace BPFunction
{
	static string TypeToString(BlueprintType type)
	{
		string typeString;
		if (type == BlueprintType::FUNCTION) typeString = "FUNCTION";
		if (type == BlueprintType::FLOAT) typeString = "FLOAT";
		if (type == BlueprintType::OBJECT) typeString = "OBJECT";
		if (type == BlueprintType::SEQUENCE) typeString = "SEQUENCE";
		if (type == BlueprintType::UI) typeString = "UI";
		return typeString;
	}
	static string SubTypeToString(BlueprintSubType subType)
	{
		string subtypeString;
		if (subType == BlueprintSubType::NONE) subtypeString = "NONE";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_BEZIER2) subtypeString = "SEQUENCE_QUEUE_BEZIER2";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_BEZIER3) subtypeString = "SEQUENCE_QUEUE_BEZIER3";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_EASEIN) subtypeString = "SEQUENCE_QUEUE_EASEIN";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_EASEINOUT) subtypeString = "SEQUENCE_QUEUE_EASEINOUT";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_EASEOUT) subtypeString = "SEQUENCE_QUEUE_EASEOUT";
		if (subType == BlueprintSubType::SEQUENCE_QUEUE_LINEAR) subtypeString = "SEQUENCE_QUEUE_LINEAR";

		if (subType == BlueprintSubType::UI_GAME_START) subtypeString = "UI_GAME_START";
		if (subType == BlueprintSubType::UI_GAME_END) subtypeString = "UI_GAME_END";
		if (subType == BlueprintSubType::UI_GAME_SAVE) subtypeString = "UI_GAME_SAVE";
		if (subType == BlueprintSubType::UI_GAME_LOAD) subtypeString = "UI_GAME_LOAD";
		if (subType == BlueprintSubType::UI_SCENE_CG) subtypeString = "UI_SCENE_CG";
		if (subType == BlueprintSubType::UI_SCENE_DIALOGUE) subtypeString = "UI_SCENE_DIALOGUE";
		if (subType == BlueprintSubType::UI_SCENE_OPTION) subtypeString = "UI_SCENE_OPTION";
		if (subType == BlueprintSubType::UI_SCENE_TITLE) subtypeString = "UI_SCENE_TITLE";
		if (subType == BlueprintSubType::UI_SCENE_SELECT) subtypeString = "UI_SCENE_SELECT";
		if (subType == BlueprintSubType::UI_SCENE_SAVE) subtypeString = "UI_SCENE_SAVE";
		return subtypeString;
	}
	static BlueprintType StringToType(string s)
	{
		BlueprintType type;
		if (s.compare("FUNCTION") == 0) type = BlueprintType::FUNCTION;
		if (s.compare("FLOAT") == 0) type = BlueprintType::FLOAT;
		if (s.compare("OBJECT") == 0) type = BlueprintType::OBJECT;
		if (s.compare("SEQUENCE") == 0) type = BlueprintType::SEQUENCE;
		if (s.compare("UI") == 0) type = BlueprintType::UI;
		return type;
	}
	static BlueprintSubType StringToSubType(string s)
	{
		BlueprintSubType subType = BlueprintSubType::NONE;
		if (s.compare("SEQUENCE_QUEUE_EASEIN") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_EASEIN;
		if (s.compare("SEQUENCE_QUEUE_EASEOUT") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_EASEOUT;
		if (s.compare("SEQUENCE_QUEUE_EASEINOUT") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_EASEINOUT;
		if (s.compare("SEQUENCE_QUEUE_LINEAR") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_LINEAR;
		if (s.compare("SEQUENCE_QUEUE_BEZIER2") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_BEZIER2;
		if (s.compare("SEQUENCE_QUEUE_BEZIER3") == 0) subType = BlueprintSubType::SEQUENCE_QUEUE_BEZIER3;

		if (s.compare("UI_GAME_START") == 0) subType = BlueprintSubType::UI_GAME_START;
		if (s.compare("UI_GAME_END") == 0) subType = BlueprintSubType::UI_GAME_END;
		if (s.compare("UI_GAME_SAVE") == 0) subType = BlueprintSubType::UI_GAME_SAVE;
		if (s.compare("UI_GAME_LOAD") == 0) subType = BlueprintSubType::UI_GAME_LOAD;
		if (s.compare("UI_SCENE_CG") == 0) subType = BlueprintSubType::UI_SCENE_CG;
		if (s.compare("UI_SCENE_DIALOGUE") == 0) subType = BlueprintSubType::UI_SCENE_DIALOGUE;
		if (s.compare("UI_SCENE_OPTION") == 0) subType = BlueprintSubType::UI_SCENE_OPTION;
		if (s.compare("UI_SCENE_SAVE") == 0) subType = BlueprintSubType::UI_SCENE_SAVE;
		if (s.compare("UI_SCENE_SELECT") == 0) subType = BlueprintSubType::UI_SCENE_SELECT;
		if (s.compare("UI_SCENE_TITLE") == 0) subType = BlueprintSubType::UI_SCENE_TITLE;
		return subType;
	}
}

class Blueprint
{
public:
	Blueprint();
	virtual ~Blueprint();
	bool Update();
	void Render();

	virtual void Load(json& data) {};
	virtual void Save(json& data, int layer, int objIndex, int bpIndex);
	virtual void Save(json& data, int objIndex, int bpIndex);
	virtual void Save(json& data, int bpIndex);

	void SetID(UINT id) { this->id = id; }
	UINT GetID() { return id; }
	
	virtual void Execute(void * data = nullptr) {};

	Object2D * GetObject2D() { return object2D; }
	BlueprintType GetType() { return type; }
	float GetColorAvg();

	BlueprintSubType GetSubType() { return subType; }
	virtual void SetSubType(BlueprintSubType type, int dataSize);

	vector<BlueprintSubData>& GetSubData() { return subData; }

protected:
	virtual void SubUpdate() {};
	virtual void SubRender() {};

	UINT id;

	Object2D * object2D;
	BlueprintType type;
	BlueprintSubType subType;

	vector<BlueprintSubData> subData;
};

class BlueprintList
{
public:
	BlueprintList(BlueprintObjectType type);
	~BlueprintList();

	Blueprint * Add(BlueprintType type);
	Blueprint * Add(Blueprint * bp);
	void Delete(BlueprintNode * node);

	void Update();
	void Render();
	void Save(json &data, int layer, int objIndex);
	void Save(json &data, int objIndex);
	void Save(json &data);
	void Clear();

	BlueprintObjectType GetType() { return type; }
	BlueprintNode * GetSelectNode() { return selectNode; }
	BlueprintNode * GetClickNode();

	void SetOffset(D3DXVECTOR3 offset) { this->offset = offset; }
	D3DXVECTOR3 GetOffset() { return offset; }
	
	void Excute(string funcName);
	void ExcuteUpdate(GameObject * gameobject);

	void Link(vector<BlueprintLinkData> linkData);

private:
	void CreateBuffer();
	void Link();
	void SetData();
	void LineRender(Blueprint * from, Blueprint * to, wstring comment = L"");
	void MouseDrag();
	BlueprintNode * FindNode(UINT id);

	VertexBuffer * vertexBuffer;
	Shader * shader;

	float elapse;

	// 블루프린트
	string inputData;
	BlueprintObjectType type;
	BlueprintNode * selectNode;

	Sequence * seq;

	// 드래그
	D3DXVECTOR3 offset;
	D3DXVECTOR3 startOffset;
	D3DXVECTOR3 startMousePos;

private:
	vector<BlueprintNode*> nodeList;
};