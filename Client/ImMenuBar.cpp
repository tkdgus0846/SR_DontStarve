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
	// �޴��� ���� �ڵ�
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

		// �߰����� �޴� �׸��� ���⿡ �ۼ��ϼ���.

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
	HANDLE		hFile = CreateFile(path,		// ���� ��ο� �̸��� ���
		GENERIC_WRITE,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
		NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
		CREATE_ALWAYS,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->WriteMapFile(hFile, dwByte);
	
	// ���� �Ҹ�
	CloseHandle(hFile);
}

void CImMenuBar::Load()
{
	const TCHAR* path = m_strFilePathName.c_str();
	HANDLE		hFile = CreateFile(path,		// ���� ��ο� �̸��� ���
		GENERIC_READ,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
		NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
		OPEN_EXISTING,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->ReadMapFile(hFile, dwByte);

	// ���� �Ҹ�
	CloseHandle(hFile);
}
