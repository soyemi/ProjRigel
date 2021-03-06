#include "rgeditor.h"
#include "rgeditor_core.h"
#include "rgeditor_module.h"

#include <imgui\imgui.h>


namespace rgeditor {
	RigelEditorCore* RigelEditorCore::m_pInstance = nullptr;
	RigelEditorCore * RigelEditorCore::getInstance()
	{
		if (m_pInstance == nullptr) {
			m_pInstance = new RigelEditorCore();
		}
		return m_pInstance;
	}

	void RigelEditorCore::release()
	{
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void RigelEditorCore::showEntryPage()
	{
		m_pInstance->m_bShowEntryPage = true;
	}

	void RigelEditorCore::projectNew(bool _tempProj)
	{
		if (_tempProj) {
			m_currentProj.tempProj = true;
			m_currentProj.valid = true;
			m_currentProj.proj_name = "Temp Proj";
			return;
		}
	}

	void RigelEditorCore::projectOpen()
	{
	}

	void RigelEditorCore::projectDirty()
	{
	}

	void RigelEditorCore::guiBasis()
	{
		guiEnteryPage();

		guiProjectInfo();


		static RigelEditorFileTree ft(L"D:/git/yemi/ProjRigel/Build/win64");

		ft.drawGUI();
	}

	void RigelEditorCore::guiMainMenuBar()
	{
		if (ImGui::BeginMenu("File")) {
			if (ImGui::BeginMenu("New")) {
				if (ImGui::MenuItem("Project")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Open")) {
				if (ImGui::MenuItem("Project")) {}
				if (ImGui::MenuItem("Show Welcome Page")) RigelEditorCore::showEntryPage();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
	}

	void RigelEditorCore::guiEnteryPage()
	{
		if (m_bShowEntryPage) {
			ImGui::OpenPopup("Hello World");
		}

		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Hello World",NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::Button("Project 1")) {

			}

			ImGui::SameLine();
			if (ImGui::Button("Project 2")) {

			}
			ImGui::Separator();

			if (ImGui::Button("Temp Project")) {
				ImGui::CloseCurrentPopup(); m_bShowEntryPage = false;
				m_pInstance->projectNew(true);
			}
			ImGui::EndPopup();
		}

		
	}

	void RigelEditorCore::guiProjectInfo()
	{
		if (!m_currentProj.valid) return;

		ImGui::SetNextWindowPos(ImVec2(0, 100), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(150, 400), ImGuiCond_FirstUseEver);
		ImGuiWindowFlags flag = ImGuiWindowFlags_NoMove;
		flag |= ImGuiWindowFlags_NoResize;
		flag |= ImGuiWindowFlags_NoCollapse;
		flag |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		flag |= ImGuiWindowFlags_NoTitleBar;
		if (ImGui::Begin("ProjectInfo",NULL, flag))
		{
			ImGui::Text(m_currentProj.proj_name.c_str());
			ImGui::Separator();
		}
		ImGui::End();
	}

	void RigelEditorCore::init()
	{
		rgEditorModuleInit();
	}

	void RigelEditorCore::shutdown()
	{
		rgEditorModuleShutdown();
	}

	void RigelEditorCore::update()
	{
		rgEditorModuleUpdate();
	}

	RigelEditorCore::~RigelEditorCore()
	{
	}

	RigelEditorFileTree::RigelEditorFileTree(std::wstring path)
	{
		namespace fs = std::experimental::filesystem;

		fs::path basepath = path;

		RGLOG_DEBUG(basepath.string().c_str());
		
		open(basepath);
	}

	void RigelEditorFileTree::open(fs::path p)
	{
		

		std::vector<fs::path>().swap(subpath);

		fs::directory_iterator diriter(p);
		for (auto d : diriter) {
			subpath.push_back(d.path());
		}

		if (m_selected != nullptr) {
			delete[]m_selected;
		}

		m_selected = new bool[subpath.size()];
		memset(m_selected, 0, sizeof(bool)* subpath.size());

		basepath = p;
	}

	void RigelEditorFileTree::drawGUI()
	{
		auto& size = ImGui::GetWindowSize();

		if (ImGui::BeginChild("corefs", ImVec2(size.x, size.y), false)) {

			int diropen = -1;
			int index = 0;

			ImGuiIO& io = ImGui::GetIO();

			bool dirp = false;
			if (ImGui::Selectable("..",&dirp, ImGuiSelectableFlags_AllowDoubleClick)) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					diropen = 0;
				}
			}

			for (auto& p : subpath) {
				std::string s = p.filename().string();
				if (ImGui::Selectable( s.c_str(), &m_selected[index],ImGuiSelectableFlags_AllowDoubleClick)) {
					if (ImGui::IsMouseDoubleClicked(0)) {
						if (fs::is_directory(p)) {
							diropen = index;
						}
					}
				}
				index++;
			}

			if (diropen >= 0) {
				if (diropen == 0) {
					open(basepath.parent_path());
				}
				else
				{
					open(subpath[diropen]);
				}
			}
		}
		ImGui::EndChild();
	}

	void RigelEditorFileTree::selectClear()
	{
		memset(m_selected, 0, sizeof(bool)* subpath.size());
	}

}

