#include "ImMenuBar.h"
#include "ImGuiFileDialog.h"
#include "Export_Function.h"
#include "FileSystem.h"
#include <tchar.h>
#include "MyMap.h"

CImMenuBar::CImMenuBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
{

}

CImMenuBar::~CImMenuBar()
{
}

HRESULT CImMenuBar::Ready_ImWindow()
{
	return S_OK;
}

_int CImMenuBar::Update(float fTimeDelta)
{
	// 메뉴바 생성 코드
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save", "Ctrl+S")) { m_bSaveButton = true; }
			if (ImGui::MenuItem("Load", "Ctrl+O")) { m_bLoadButton = true; }
			ImGui::Separator();
			//if (ImGui::MenuItem("Quit", "Alt+F4")) { glfwSetWindowShouldClose(window, 1); }
			ImGui::EndMenu();
		}

		// 추가적인 메뉴 항목을 여기에 작성하세요.

		ImGui::EndMainMenuBar();
	}

	if (m_bSaveButton)
		SaveFileDialog();

	if (m_bLoadButton)
		LoadFileDialog();


	return 0;
}

CImMenuBar * CImMenuBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImMenuBar* pInstance = new CImMenuBar(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImMenuBar::Free(void)
{
	__super::Free();
}

void CImMenuBar::SaveFileDialog()
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File"
		, ".dat,.hpp", ".", 1, nullptr
		, ImGuiFileDialogFlags_ConfirmOverwrite);

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			m_strFilePathName = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetFilePathName());
			m_strFilePath = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetCurrentPath());
			m_strFileName = CFileSystem::strToWStr(CFileSystem::FileNameFromPath(CFileSystem::wstrToStr(m_strFilePathName)));

			Save();
			m_bSaveButton = false;
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}

void CImMenuBar::LoadFileDialog()
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.hpp,.dat", ".");

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			m_strFilePathName = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetFilePathName());
			m_strFilePath = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetCurrentPath());
			m_strFileName = CFileSystem::strToWStr(CFileSystem::FileNameFromPath(CFileSystem::wstrToStr(m_strFilePathName)));

			Load();
			m_bLoadButton = false;
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}

void CImMenuBar::Save()
{
	const TCHAR* path = m_strFilePathName.c_str();
	HANDLE		hFile = CreateFile(path,		// 파일 경로와 이름을 명시
		GENERIC_WRITE,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
		NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
		CREATE_ALWAYS,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->WriteMapFile(hFile, dwByte);
	
	// 파일 소멸
	CloseHandle(hFile);
}

void CImMenuBar::Load()
{
	const TCHAR* path = m_strFilePathName.c_str();
	HANDLE		hFile = CreateFile(path,		// 파일 경로와 이름을 명시
		GENERIC_READ,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
		NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
		OPEN_EXISTING,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->ReadMapFile(hFile, dwByte);

	// 파일 소멸
	CloseHandle(hFile);
}
