#include "stdafx.h"
#include "DInputMgr.h"

IMPLEMENT_SINGLETON(CDInputMgr)

CDInputMgr::CDInputMgr()
	: m_pInputSDK(nullptr)
	, m_pKeyBoard(nullptr)
	, m_pMouse(nullptr)
{
	ZeroMemory(m_byKeyState, sizeof(m_byKeyState));
	ZeroMemory(m_byPreKeyState, sizeof(m_byKeyState));
	ZeroMemory(&m_tMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_tPreMouseState, sizeof(DIMOUSESTATE));
}


CDInputMgr::~CDInputMgr()
{
	Free();
}

HRESULT CDInputMgr::Ready_DInput(HINSTANCE hInst, HWND hWnd)
{
	// 부모 컴객체 생성
	FAILED_CHECK_RETURN(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputSDK, nullptr), E_FAIL);

	// 내 컴퓨터에 연결되어 있는 키보드 객체 생성
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

	// 생성된 키보드 객체애 대한 정보를 컴객체에게 전달
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 생성된 키보드 객체의 동작 범위를 설정
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 생성된 키보드 컴객체를 활성화
	m_pKeyBoard->Acquire();

	// 내 컴퓨터에 연결되어 있는 마우스 객체 생성
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// 생성된 마우스 객체애 대한 정보를 컴객체에게 전달
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 생성된 마우스 객체의 동작 범위를 설정
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 생성된 마우스 컴객체를 활성화
	m_pMouse->Acquire();

	return S_OK;
}

void CDInputMgr::Update_DInput(void)
{
	memcpy(m_byPreKeyState, m_byKeyState, sizeof(_byte) * MAX_DIK);
	memcpy(&m_tPreMouseState, &m_tMouseState, sizeof(DIMOUSESTATE));

	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

bool CDInputMgr::Key_Pressing(_ubyte ubyKey)
{
	if ((m_byPreKeyState[ubyKey] & 0x80) && (m_byKeyState[ubyKey] & 0x80))
		return true;

	return false;
}

bool CDInputMgr::Key_Down(_ubyte ubyKey)
{
	if (!(m_byPreKeyState[ubyKey] & 0x80) && (m_byKeyState[ubyKey] & 0x80))
		return true;

	return false;
}

bool CDInputMgr::Key_Up(_ubyte ubyKey)
{
	if ((m_byPreKeyState[ubyKey] & 0x80) && !(m_byKeyState[ubyKey] & 0x80))
		return true;

	return false;
}

bool CDInputMgr::Mouse_Down(MOUSEKEYSTATE eMouseID)
{
	if (!m_tPreMouseState.rgbButtons[eMouseID] && m_tMouseState.rgbButtons[eMouseID])
		return true;

	return false;
}

bool CDInputMgr::Mouse_Pressing(MOUSEKEYSTATE eMouseID)
{
	if (m_tPreMouseState.rgbButtons[eMouseID] && m_tMouseState.rgbButtons[eMouseID])
		return true;

	return false;
}

bool CDInputMgr::Mouse_Up(MOUSEKEYSTATE eMouseID)
{
	if (m_tPreMouseState.rgbButtons[eMouseID] && !m_tMouseState.rgbButtons[eMouseID])
		return true;

	return false;
}

void Engine::CDInputMgr::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}
