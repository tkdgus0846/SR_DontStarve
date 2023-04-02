#pragma once

#include "Management.h"
#include "ProtoMgr.h"
#include "Renderer.h"
#include "CollisionMgr.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "TerrainTex.h"
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

#include "LightMgr.h"

#include "Root.h"
#include "AIRoot.h"
#include "ChasePlayer.h"
#include "MoveLook.h"
#include "BlackBoard.h"

BEGIN(Engine)

inline HRESULT			Create_Management(CManagement** ppManagement);

inline CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

inline HRESULT			Set_Scene(CScene* pScene);

inline _int			Update_Management(const _float& fTimeDelta);
inline void			LateUpdate_Management();
inline void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev);


inline HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject, class CBlackBoard* pBlackBoard = nullptr);


inline void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
inline void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void		Clear_RenderGroup(void);

inline void		Add_Collider(COLGROUP eID, CCollider* pCollider);
inline void		Check_Collision();
inline void		Clear_Collision();

inline void		On_Camera(const _tchar* pCamTag);
inline void		Shake_Camera();

inline HRESULT			Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);
inline void						Release_Utility(void);


#include "Export_Utility.inl"

END