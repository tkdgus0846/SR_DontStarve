#pragma once

#include "Management.h"
#include "ProtoMgr.h"
#include "Renderer.h"
#include "CollisionMgr.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"

#include "Collider.h"

#include "GameObject.h"

#include "Transform.h"
#include "Texture.h"
#include "Camera.h"
#include "CubeTex.h"
#include "Rigidbody.h"
#include "CameraMgr.h"
#include "RoomTex.h"
#include "Mesh.h"
#include "FloorTex.h"
#include "WallTex.h"

#include "LightMgr.h"

#include "Root.h"
#include "Sequence.h"
#include "Selector.h"
#include "Wait.h"
#include "MoveLook.h"
#include "RotToFace.h"
#include "RandomLook.h"	
#include "BlackBoard.h"
#include "Animation.h"

BEGIN(Engine)

inline HRESULT			Create_Management(CManagement** ppManagement);

inline CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

inline void			Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj);

inline HRESULT			Set_Scene(CScene* pScene);

inline _int			Update_Management(const _float& fTimeDelta);
inline void			LateUpdate_Management();
inline void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev);


inline HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);

inline CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject);
// AI 클론용
inline CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, class CBlackBoard* pBlackBoard);

// Collider 클론용
inline CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize = { 2.f,2.f,2.f });


inline void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
inline void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void		Clear_RenderGroup(void);

inline void		Add_Collider(COLGROUP eID, CCollider * pCollider);
inline void		Check_Collision(COLGROUP eGroup1, COLGROUP eGroup2);
inline void		Toggle_ColliderRender();
inline void		Change_ColGroup(CCollider* collider, COLGROUP changeID);
//inline void		Set_Collider(COLGROUP eGroup, CCollider* pCollider);
//
inline void		On_Camera(const _tchar* pCamTag);
inline void		Shake_Camera();

inline HRESULT			Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);
inline void						Release_Utility(void);


#include "Export_Utility.inl"

END