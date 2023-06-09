#include "ImInspector.h"

#include "Export_Function.h"

#include "EditCamera.h"

#include "Room.h"
#include "RoomMgr.h"

#include "Baller.h"
#include "Bub.h"
#include "Guppi.h"
#include "Turret.h"
#include "Walker.h"

CImInspector::CImInspector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev), m_pCurTarget(nullptr)
	, m_pCurRoom(nullptr)
{
	ZeroMemory(m_vObjectPos, sizeof(_vec3));
}

CImInspector::~CImInspector()
{
}

HRESULT CImInspector::Ready_ImWindow()
{
	return S_OK;
}

_int CImInspector::Update(float fTimeDelta)
{
	for(auto iter : m_vecMonster)
		iter.second->Update_GameObject(fTimeDelta);

	ImGui::Begin("Inspector");

	if (ImGui::CollapsingHeader("RommInfo"))
		Show_RoomInfo();

	if (ImGui::CollapsingHeader("TilePicking"))
		Show_TilePicking();

	if (ImGui::CollapsingHeader("CreateObject"))
		Show_Create_Object();

	if (ImGui::CollapsingHeader("ObjectList"))
		Show_MonsterList();

	if(ImGui::CollapsingHeader("Components"))
		Show_Components();

	ImGui::End();

	return 0;
}

void CImInspector::Show_RoomInfo()
{
	const char* items[25] = { "0", "1", "2", "3", "4",
		"5", "6", "7", "8", "9",
		"10", "11", "12", "13", "14",
		"15", "16", "17", "18", "19",
		"20", "21", "22", "23", "24" };
	static int item_current = 0;
	ImGui::Combo("Room_Index", &item_current, items, IM_ARRAYSIZE(items));

	m_vObjectPos.x = _float(item_current % 5 * 60 + 5);
	m_vObjectPos.y = 5.f;
	m_vObjectPos.z = _float(item_current / 5 * 60 + 5);

	CEditCamera* pCamera = dynamic_cast<CEditCamera*>(Get_GameObject(LAYER_CAMERA, L"Edit_Camera"));
	pCamera->m_pTransform->m_vInfo[INFO_POS] = { m_vObjectPos.x + 25.f, 25.f, m_vObjectPos.z + 25.f };
	ROOM_MGR->Set_CurRoom(item_current);
	m_pCurRoom = ROOM_MGR->Get_CurRoom();

	static _int iObjNum = 0, iPre = 0;

	ImGui::RadioButton("DOOR_ES", &iObjNum, 0); ImGui::SameLine();
	ImGui::RadioButton("DOOR_ESW", &iObjNum, 1); ImGui::SameLine();
	ImGui::RadioButton("DOOR_EW", &iObjNum, 2);
	ImGui::RadioButton("DOOR_N", &iObjNum, 3); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NE", &iObjNum, 4);
	ImGui::RadioButton("DOOR_NES", &iObjNum, 5); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NESW", &iObjNum, 6); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NS", &iObjNum, 7);
	ImGui::RadioButton("DOOR_NW", &iObjNum, 8); ImGui::SameLine();
	ImGui::RadioButton("DOOR_S", &iObjNum, 9);
	ImGui::RadioButton("DOOR_SW", &iObjNum, 10); ImGui::SameLine();
	ImGui::RadioButton("DOOR_SWN", &iObjNum, 11); ImGui::SameLine();
	ImGui::RadioButton("DOOR_W", &iObjNum, 12);
	ImGui::RadioButton("DOOR_WNE", &iObjNum, 13); ImGui::SameLine();
	ImGui::RadioButton("DOOR_E", &iObjNum, 14);

	if (iPre != iObjNum)
	{
		m_pCurRoom->Set_DoorType((DOOR_TYPE)iObjNum);
		iPre = iObjNum;
	}
}

void CImInspector::Show_TilePicking()
{
	static _int iTileNum = 0;

	ImGui::Begin("Image");
	Show_Image(iTileNum);
	ImGui::End();

	CEditCamera* pCamera = dynamic_cast<CEditCamera*>(Get_GameObject(LAYER_CAMERA, L"Edit_Camera"));

	ImGui::Checkbox("CHECK_PICK!", &pCamera->Get_Pick());
	ImGui::SeparatorText("Tile");

	if (ImGui::RadioButton("Level1_Floor", &iTileNum, 20))
		pCamera->Change_Texture(L"Floor_Level1_Texture");

	ImGui::SameLine();

	if (ImGui::RadioButton("Level1_Wall", &iTileNum, 21))
		pCamera->Change_Texture(L"Wall_Level1_Texture");

	if(ImGui::RadioButton("Level2_Floor", &iTileNum, 22))
		pCamera->Change_Texture(L"Floor_Level2_Texture");

	ImGui::SameLine();

	if(ImGui::RadioButton("Level2_Wall", &iTileNum, 23))
		pCamera->Change_Texture(L"Wall_Level2_Texture");

	if(ImGui::RadioButton("Level3_Floor", &iTileNum, 24))
		pCamera->Change_Texture(L"Dock_Texture");

	ImGui::SameLine();
	ImGui::RadioButton("Level3_Wall", &iTileNum, 25);
}

void CImInspector::Show_Create_Object()
{
	static _int iObjNum = 0;

	if (ImGui::TreeNode("Object_Type"))
	{
		ImGui::Begin("Image");
		Show_Image(iObjNum);
		ImGui::End();

		ImGui::SeparatorText("Monster");

		ImGui::RadioButton("Baller", &iObjNum, 0); ImGui::SameLine();
		ImGui::RadioButton("Bub", &iObjNum, 1); ImGui::SameLine();
		ImGui::RadioButton("Guppi", &iObjNum, 2);
		ImGui::RadioButton("Turret", &iObjNum, 3); ImGui::SameLine();
		ImGui::RadioButton("Walker", &iObjNum, 4);

		ImGui::SeparatorText("Environment");

		ImGui::RadioButton("Dirt_Barrier", &iObjNum, 11); ImGui::SameLine();
		ImGui::RadioButton("Mine", &iObjNum, 12);

		ImGui::TreePop();
		ImGui::Spacing();
	}

	if (ImGui::TreeNode("Object_Info"))
	{
		ImGui::SeparatorText("Transform");

		ImGui::SeparatorText("Collider");

		ImGui::TreePop();
		ImGui::Spacing();
	}

	if(ImGui::Button("CREATE!"))
	{
		CGameObject* pGameObject = nullptr;
		const char* pName = nullptr;

		if (0 == iObjNum)
		{
			pName = "Baller";
			pGameObject = CBaller::Create(m_pGraphicDev, m_vObjectPos);
			m_pCurRoom->PushBack_GameObj(pGameObject);
		}
		if (1 == iObjNum)
		{
			pName = "Bub";
			pGameObject = CBub::Create(m_pGraphicDev, m_vObjectPos);

			m_pCurRoom->PushBack_GameObj(pGameObject);
		}

		if (2 == iObjNum)
		{
			pName = "Guppi";
			pGameObject = CGuppi::Create(m_pGraphicDev, m_vObjectPos);
			m_pCurRoom->PushBack_GameObj(pGameObject);
		}
		if (3 == iObjNum)
		{
			pName = "Turret";
			pGameObject = CTurret::Create(m_pGraphicDev, m_vObjectPos);
			m_pCurRoom->PushBack_GameObj(pGameObject);
		}
		if (4 == iObjNum)
		{
			pName = "Walker";
			pGameObject = CWalker::Create(m_pGraphicDev, m_vObjectPos);
			m_pCurRoom->PushBack_GameObj(pGameObject);
		}

		m_vecMonster.push_back({ pName, pGameObject });
	}
}

void CImInspector::Show_MonsterList()
{
	static _int iCurItemIdx = 0;

	if (ImGui::BeginListBox("Monster"))
	{
		for (_uint i = 0; i < m_vecMonster.size(); ++i)
		{
			bool is_selected = (iCurItemIdx == i);
			if (ImGui::Selectable(m_vecMonster[i].first, is_selected, 4914304))
			{
				m_pCurTarget = m_vecMonster[i].second;
				iCurItemIdx = i;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}
	if (ImGui::BeginListBox("Environment"))
	{
		ImGui::EndListBox();
	}
	if (ImGui::BeginListBox("Tile"))
	{
		ImGui::EndListBox();
	}
}

void CImInspector::Show_Components()
{
	if (nullptr == m_pCurTarget)
		return;

	auto uMapComponent = m_pCurTarget->Get_ComponentMap();

	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : uMapComponent[i])
		{
			if (CTransform* pTrans = dynamic_cast<CTransform*>(iter.second))
			{
				if (ImGui::TreeNode("Transform"))
				{
					ImGui::SeparatorText("Info_Pos");

					ImGui::DragFloat("Pos_X", &pTrans->m_vInfo[INFO_POS].x, 0.01f);
					ImGui::DragFloat("Pos_Y", &pTrans->m_vInfo[INFO_POS].y, 0.01f);
					ImGui::DragFloat("Pos_Z", &pTrans->m_vInfo[INFO_POS].z, 0.01f);

					ImGui::SeparatorText("Info_Rotation");

					static _float fAngleX = 0.f;
					static _float fAngleY = 0.f;
					static _float fAngleZ = 0.f;

					ImGui::DragFloat("Rot_X", &fAngleX, 0.1f);
					ImGui::DragFloat("Rot_Y", &fAngleY, 0.1f);
					ImGui::DragFloat("Rot_Z", &fAngleZ, 0.1f);

					pTrans->m_vInfo[INFO_RIGHT] =	{ 1.f, 0.f, 0.f };
					pTrans->m_vInfo[INFO_UP]	=	{ 0.f, 1.f, 0.f };
					pTrans->m_vInfo[INFO_LOOK]	=	{ 0.f, 0.f, 1.f };

					pTrans->Rot_Pitch(fAngleX, 1.f);
					pTrans->Rot_Yaw(fAngleY, 1.f);
					pTrans->Rot_Roll(fAngleZ, 1.f);

					ImGui::SeparatorText("Info_Scale");

					ImGui::DragFloat("Scale_X", &pTrans->m_vScale.x, 0.01f);
					ImGui::DragFloat("Scale_Y", &pTrans->m_vScale.y, 0.01f);
					ImGui::DragFloat("Scale_Z", &pTrans->m_vScale.z, 0.01f);

					_float fAll = 0.f;
					ImGui::DragFloat("Scale_XYZ", &fAll, 0.01f);
					pTrans->m_vScale.x += fAll;
					pTrans->m_vScale.y += fAll;
					pTrans->m_vScale.z += fAll;

					ImGui::TreePop();
					ImGui::Spacing();
				}
			}
			if (CCollider* pCollider = dynamic_cast<CCollider*>(iter.second))
			{
				char* p = (char*)iter.first;

				if (ImGui::TreeNode(p))
				{
					if (false == pCollider->Toggle_IsRender())
						pCollider->Toggle_IsRender();

					_float fLength = 0.f;
					_vec3 vBoundSize(0.f, 0.f, 0.f);

					ImGui::DragFloat("Len_X", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x + fLength, vBoundSize.y, vBoundSize.z });

					fLength = 0.f;
					ImGui::DragFloat("Len_Y", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x, vBoundSize.y + fLength, vBoundSize.z });

					fLength = 0.f;
					ImGui::DragFloat("Len_Z", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x, vBoundSize.y, vBoundSize.z + fLength });

					fLength = 0.f;
					ImGui::DragFloat("Len_XYZ", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x + fLength, vBoundSize.y + fLength, vBoundSize.z + fLength });

					ImGui::TreePop();
					ImGui::Spacing();
				}
				else if(true == pCollider->Toggle_IsRender())
					pCollider->Toggle_IsRender();
			}
			if (dynamic_cast<CCamera*>(iter.second))
			{
				if (ImGui::TreeNode("Camera"))
				{
					ImGui::Text("Camera");
					ImGui::TreePop();
					ImGui::Spacing();
				}
			}
		}
	}
}

void CImInspector::Show_Image(_int iObjNum)
{
	CTexture* pTexture = nullptr;
	if (0 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Baller_Texture", nullptr));
	if (1 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Bub_Texture", nullptr));
	if (2 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Guppi_Blue_Texture", nullptr));
	if (3 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Turret_Texture", nullptr));
	if (4 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Walker_Texture", nullptr));


	if (20 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Level1_Texture", nullptr));
	if (21 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Wall_Level1_Texture", nullptr));
	if (22 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Level2_Texture", nullptr));
	if (23 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Wall_Level2_Texture", nullptr));
	if (24 == iObjNum)
		pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Dock_Texture", nullptr));

	if(pTexture)
		ImGui::Image((void*)pTexture->Get_TextureCom(), ImVec2(100.f, 100.f));
}

CImInspector * CImInspector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImInspector* pInstance = new CImInspector(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImInspector::Free(void)
{
	__super::Free();
}
