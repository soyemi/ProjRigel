#include "stdafx.h"
#include "editor_gui.h"
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_bind_graphics.h>

using namespace rg;

namespace editor {
	EditorGUI::EditorGUI()
	{
		RgGUI::CreateRgGUIContext(&m_pGUIContext);
	}
	EditorGUI::~EditorGUI()
	{
		Release();
	}
	void EditorGUI::Release()
	{
		if(m_pBindGraphics != nullptr)
			m_pBindGraphics->Release();
		m_pBindGraphics = nullptr;

		RgGUI::Release(&m_pGUIContext);
	}
	void EditorGUI::BindGraphics(rg::RgGraphicsContext * graphicsCtx)
	{
		if (m_pBindGraphics != nullptr) {
			m_pBindGraphics->Release();
		}
		m_pBindGraphics = new RgGUIBindGraphics(m_pGUIContext, graphicsCtx);
	}
	void EditorGUI::OnWindowGUI(const rg::RgWindowEvent e)
	{
		if (e.Type == RgWindowEventType::Resize) {
			RgLogW() << "resize";
			m_pBindGraphics->ReBuildCommandList();
		}
	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


