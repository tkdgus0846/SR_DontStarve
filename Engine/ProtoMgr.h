#pragma once

#include "Include.h"
#include "Base.h"

BEGIN(Engine)

class  CProtoMgr : public CBase
{
	DECLARE_SINGLETON(CProtoMgr)

private:
	explicit CProtoMgr(void);
	virtual ~CProtoMgr(void);

public:
	HRESULT		Ready_Proto(const _tchar* pProtoTag, class CComponent* pComponent);
	
	// 기본 클론
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject);

	// AI 클론용
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, class CBlackBoard* pBlackBoard);

	// Collider 클론용
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize = {2.f,2.f,2.f});

private:
	class CComponent*	Find_Proto(const _tchar* pProtoTag);

private:
	unordered_map<const _tchar*, class CComponent*>			m_uMapProto;

private:
	virtual void Free(void);
};

END