#include "ImInspector.h"

#include "Export_Function.h"

#include "Baller.h"
#include "Bub.h"
#include "Guppi.h"
#include "Turret.h"
#include "Walker.h"

CImInspector::CImInspector(LPDIRECT3DDEVICE9 pGraphicDev)
	:CImWindow(pGraphicDev), m_pCurTarget(nullptr)
{
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

	if (ImGui::CollapsingHeader("CreateObject"))
		Show_Create_Object();

	if (ImGui::CollapsingHeader("ObjectList"))
		Show_MonsterList();

	if(ImGui::CollapsingHeader("Components"))
		Show_Components();

	ImGui::End();

	return 0;
}

void CImInspector::Show_Create_Object()
{
	CGameObject* pGameObject = nullptr;

	static int iObjNum = 0;

	if (ImGui::TreeNode("Object_Type"))
	{
		ImGui::SeparatorText("Monster");

		ImGui::RadioButton("Baller", &iObjNum, 0); ImGui::SameLine();
		ImGui::RadioButton("Bub", &iObjNum, 1); ImGui::SameLine();
		ImGui::RadioButton("Guppi", &iObjNum, 2);
		ImGui::RadioButton("Turret", &iObjNum, 3); ImGui::SameLine();
		ImGui::RadioButton("Walker", &iObjNum, 4);

		ImGui::SeparatorText("Environment");

		ImGui::RadioButton("Door", &iObjNum, 10); ImGui::SameLine();
		ImGui::RadioButton("Dirt_Barrier", &iObjNum, 11); ImGui::SameLine();
		ImGui::RadioButton("Mine", &iObjNum, 12);

		ImGui::SeparatorText("Tile");

		ImGui::RadioButton("Level1_Floor", &iObjNum, 20); ImGui::SameLine();
		ImGui::RadioButton("Level1_Wall", &iObjNum, 21);
		ImGui::RadioButton("Level2_Floor", &iObjNum, 22); ImGui::SameLine();
		ImGui::RadioButton("Level2_Wall", &iObjNum, 23);
		ImGui::RadioButton("Level3_Floor", &iObjNum, 24); ImGui::SameLine();
		ImGui::RadioButton("Level3_Wall", &iObjNum, 25);

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
		char* pName = nullptr;

		if (0 == iObjNum)
		{
			pName = "Baller";
			pGameObject = CBaller::Create(m_pGraphicDev);
		}
		if (1 == iObjNum)
		{
			pName = "Bub";
			pGameObject = CBub::Create(m_pGraphicDev);
		}
		if (2 == iObjNum)
		{
			pName = "Guppi";
			pGameObject = CGuppi::Create(m_pGraphicDev);
		}
		if (3 == iObjNum)
		{
			pName = "Turret";
			pGameObject = CTurret::Create(m_pGraphicDev);
		}
		if (4 == iObjNum)
		{
			pName = "Walker";
			pGameObject = CWalker::Create(m_pGraphicDev);
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
			const bool is_selected = (iCurItemIdx == i);
			if (ImGui::Selectable(m_vecMonster[i].first, is_selected))
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
	for (auto iter : m_vecMonster)
		Safe_Release(iter);

	__super::Free();
}
