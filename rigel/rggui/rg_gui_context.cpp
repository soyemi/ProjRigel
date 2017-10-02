#include "rggui.h"

#include "rg_gui_context.h"
#include "rg_gui_draw_buffer.h"
#include "rg_gui_glyph.h"
#include <map>

namespace rg {
	void RgGUIContext::Release()
	{
		if (m_pBufferText != nullptr) {
			delete m_pBufferText;
			m_pBufferText = nullptr;
		}
		if (m_pBufferVertex != nullptr) {
			delete m_pBufferVertex;
			m_pBufferVertex = nullptr;
		}
		if (m_pBufferIndices != nullptr) {
			delete m_pBufferIndices;
			m_pBufferIndices = nullptr;
		}

		if (m_pGlyph != nullptr) {
			m_pGlyph->Release();
			m_pGlyph = nullptr;
		}

		m_pWindowInput = nullptr;
	}
	void RgGUIContext::Reset()
	{
	}
	void RgGUIContext::SetDirty(bool dirty)
	{
		m_bDirty = dirty;
	}
	bool RgGUIContext::IsDirty()
	{
		return m_bDirty;
	}

#pragma region GUILayout
	void RgGUIContext::GUILayoutText()
	{
	}
	void RgGUIContext::GUILayoutButton()
	{
	}
	void RgGUIContext::GUILayoutGroupBegin()
	{
	}
	void RgGUIContext::GUILayoutGroupEnd()
	{
	}
	void RgGUIContext::GUILayoutRect()
	{
	}
#pragma endregion


	void RgGUIContext::gui_begin(const RgWindowEvent& e)
	{
		RgLogW() << "------------------------------";
		m_pWindowInput = e.Input;

		//state process input
		m_state.ongui(m_pWindowInput);
		//proces window;
		m_stateWindow.ongui(m_state,this);

		static bool drawed = false;
		if (drawed == false) {
			drawed = true;
		}

	}
	void RgGUIContext::gui_end()
	{
		m_stateWindow.endgui(m_state, this);

		SetDirty(true);

	}

#pragma region Buffers
	RgGUIVertexBuffer * RgGUIContext::GetVertexBufferPtr()
	{
		return m_pBufferVertex;
	}

	RgGUIVertexBuffer * RgGUIContext::GetTextBufferPtr()
	{
		return m_pBufferText;
	}

	RgGUIIndicesBuffer * RgGUIContext::GetIndicesBufferPtr()
	{
		return m_pBufferIndices;
	}
#pragma endregion


#pragma region TextDraw
	void RgGUIContext::GUIText(std::string content, const RgVec4 & rect)
	{

	}
	const RgVec2 RgGUIContext::GUIText(const char & c, const RgVec4 & rect)
	{
		//auto color = m_state.color;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy(), m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->color = color;
		//m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 0);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c, 1), m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->color = color;
		//m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 1);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c, 2), m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->color = color;
		//m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 2);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c, 3), m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->color = color;
		//m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 3);
		//m_pTextBuffer->m_pPos++;

		//return m_pGlyph->GetCharPos(c, 2);
	}
	void RgGUIContext::GUITextDebug(const RgVec4 & rect)
	{
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.x, rect.y, m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->uv = RgVec2(0, 0);
		//m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.x + rect.z, rect.y, m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->uv = RgVec2(1, 0);
		//m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + rect.zw(), m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->uv = RgVec2(1, 1);
		//m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		//m_pTextBuffer->m_pPos++;
		//m_pTextBuffer->m_pPos->pos = RgVec4(rect.x, rect.y + rect.w, m_state.RectZ, 1.0);
		//m_pTextBuffer->m_pPos->uv = RgVec2(0, 1);
		//m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		//m_pTextBuffer->m_pPos++;
		//m_state.rect_z_inc();
	}
#pragma endregion


	void RgGUIContext::GUIMenuBarBegin(const RgVec4 & rect)
	{
		//GUIGroupBegin(rect, m_style.MenuBarBackgroudColor);
		//m_state.guiMenuBar = true;
		//m_state.guiMenuBarOffset = 0;
		//m_state.guiMenuBarHeight = rect.w;
	}

	void RgGUIContext::GUIMenuBarEnd()
	{
		//m_state.guiMenuBar = false;
		//GUIGroupEnd();
		
	}

	bool RgGUIContext::GUIMenuItem(RgFloat width)
	{
		//bool clicked = GUIButton(RgVec2(m_state.guiMenuBarOffset, 0.0f), RgVec2(width, m_state.guiMenuBarHeight));
		//m_state.guiMenuBarOffset += width;
		//return clicked;
		return false;
	}

	void RgGUIContext::GUIMenuListBegin(RgStr label, RgFloat width)
	{
		//bool clicked = GUIMenuItem(width);
		//if (clicked) {
		//	SetColor(RgGUIColors::Alizarin);

		//	RgVec4 rect(400, 400, 100, 200);
		//	int ctxmenu = UtilGetHash(label, RgGUIControllerType::ContextMenu, rect);
		//	m_state.contextMenuAdd(ctxmenu, rect);
		//}
	}

	void RgGUIContext::GUIMenuListEnd()
	{
	}

	void RgGUIContext::GUIMenuBar(const RgGUIGenericMenu * _menu, const RgVec4 & _rect)
	{

	}

#pragma region Utility
	bool RgGUIContext::UtilIsInGroup() const
	{
		return !m_state.GroupRectStack.empty();
	}

	bool RgGUIContext::UtilClipRect(RgVec4 & content, const RgVec4 & rect) const
	{
		auto cxy = content.xy();
		auto rxy = rect.xy();

		RgVec2 lt = max(cxy, rxy);
		RgVec2 rb = min(cxy + content.zw(), rxy + rect.zw());

		if (lt.x > rb.x || lt.y > rb.y) return false;

		content.setxy(lt);
		content.setzw(rb - lt);
		return true;
	}

	const RgVec4 RgGUIContext::UtilGetOriginRect(const RgVec4 & rect) const
	{
		if (!UtilIsInGroup()) return rect;

		RgVec4 grect = rect;
		grect.setxy(rect.xy() + m_state.GroupRectStack.top().xy());
		UtilClipRect(grect, m_state.GroupRectStack.top());

		return grect;
	}

	const RgVec2 RgGUIContext::UtilGetOriginPos(const RgVec2 & lp) const
	{
		if (m_state.GroupRectStack.empty()) return lp;
		return lp + m_state.GroupRectStack.top().xy();
	}

	int RgGUIContext::UtilGetHash(RgStr label, const RgGUIControllerType type, const RgVec4 & rect)
	{
		byte data[64];
		byte* data_ptr = &data[0];
		ZeroMemory(data_ptr, 64);
		size_t labelt = label.size() > 32 ? 32 : label.size();
		memcpy(data_ptr, label.data(), labelt);
		data_ptr += 32;

		memcpy(data_ptr, &rect, sizeof(RgVec4));
		data_ptr += 16;
		byte t = (unsigned char)type;
		data_ptr[0] = t;

		return RgHash(&data[0], 64);
	}

	bool RgGUIContext::UtilRectContain(const RgVec4 & rect, const RgVec2 & pos)
	{
		if (pos.x > rect.x && pos.y > rect.y && pos.x < rect.x + rect.z && pos.y < rect.y + rect.w) {
			return true;
		}
		return false;
	}
#pragma endregion

	

	void RgGUIContext::SetColor(RgVec4 color)
	{
		m_state.color = color;
	}


	

	//pos sz in related to group root
	bool RgGUIContext::Clip(const RgVec4 & rect, RgVec2 & pos, RgVec2 & sz) const
	{
		RgVec2 rroot = max(RgVec2(), pos);
		RgVec2 rtail = pos + sz;
		rtail = min(rtail, rect.zw());

		if (rtail.x < rroot.x || rtail.y < rroot.y) return false;

		sz = rtail - rroot;
		pos = rroot + rect.xy();
		

		return true;
	}

	void RgGUIContext::RestoreColor()
	{
		m_state.colorRestored = m_state.color;
	}

	void RgGUIContext::RestoreColor(const RgVec4 & tempcolor)
	{
		RestoreColor();
		m_state.color = tempcolor;
	}

	void RgGUIContext::DropColor()
	{
		m_state.color = m_state.colorRestored;
	}

#pragma region internal
	bool RgGUIContext::_GroupClip(RgVec2 & pos, RgVec2 & sz) const
	{
		if (m_state.GroupRectStack.empty()) return true;

		return Clip(m_state.GroupRectStack.top(), pos, sz);

	}

	const RgVec2 RgGUIContext::_GetWindowSize() const
	{
		return m_pWindowInput->WindowRect.zw();
	}

	const RgVec4 RgGUIContext::_GetGroupRect() const
	{
		if (m_state.GroupRectStack.empty()) return m_state.WindowGroupRect;

		return m_state.GroupRectStack.top();
	}

	const RgFloat RgGUIContext::_GetDrawOrder()
	{
		return m_stateWindow.stateWindowOrder + m_state.currentDrawOrder;
	}


	void RgGUIContext::_DrawRect(const RgVec2 & lp, const RgVec2 & sz, const RgVec4 & color, RgFloat order)
	{

		m_pBufferVertex->ptrFloater->pos = RgVec4(lp, order, 1.0f);
		m_pBufferVertex->ptrFloater->color = color;
		m_pBufferVertex->ptrFloater++;
		m_pBufferVertex->ptrFloater->pos = RgVec4(lp.x + sz.x, lp.y, order, 1.0f);
		m_pBufferVertex->ptrFloater->color = color;
		m_pBufferVertex->ptrFloater++;
		m_pBufferVertex->ptrFloater->pos = RgVec4(lp + sz, order, 1.0f);
		m_pBufferVertex->ptrFloater->color = color;
		m_pBufferVertex->ptrFloater++;
		m_pBufferVertex->ptrFloater->pos = RgVec4(lp.x, lp.y + sz.y, order, 1.0f);
		m_pBufferVertex->ptrFloater->color = color;
		m_pBufferVertex->ptrFloater++;

		m_pBufferVertex->ExtendVertexBufferCheck();

		m_pBufferVertex->SetDirty(true);
	}

	void RgGUIContext::_GroupBegin(const RgVec2 & lp, const RgVec2 & sz)
	{
		auto&stack = m_state.GroupRectStack;
		if (stack.empty()) {
			stack.push(RgVec4(lp, sz));
		}
		else {
			RgVec4 rect = stack.top();
			rect.setxy(rect.xy() + lp);
			rect.setzw(min(lp + sz, rect.zw()) - lp);

			stack.push(rect);
		}
	}
	void RgGUIContext::_GroupEnd()
	{
		if (!m_state.GroupRectStack.empty()) m_state.GroupRectStack.pop();
	}
#pragma endregion
	

	

#pragma region GUIWindow
	bool RgGUIContext::GUIWindowBegin(RgGUIWindow* win)
	{
		//check
		assert(win != nullptr);
		if (m_stateWindow.stateWindow != nullptr) {
			RgLogE() << "invalid call: window begin";
			return false;
		}

		m_stateWindow.stateWindow = win;

		//init draw
		if (m_stateWindow.GetWindow(win->winid) == nullptr) {
			m_stateWindow.register_win(win);
			RgLogD() << "init draw" << win->title;
			m_state.ResetDrawOrder();
			m_stateWindow.DrawWindow(win, this);
			return true;
		}

		//skip draw
		if (m_stateWindow.skipDraw) {
			RgLogD() << "skip draw" << win->title;
			return false;
		}

		//focused draw
		if (win->_isfocused) {
			m_stateWindow.DrawWindow(win, this);
			return true;
		}
		RgLogD() << "win not focused" << win->title;

		return false;
	}

	void RgGUIContext::GUIWindowEnd()
	{
		auto win = m_stateWindow.stateWindow;
		if (win == nullptr) {
			RgLogE() << "invalid call�� window end";
			return;
		}
		m_stateWindow.stateWindow = nullptr;

		if (win->_ondraw) {
			m_stateWindow.DrawWindowEnd(win, this);
			return;
		}

		if (m_stateWindow.skipDraw) {
			return;
		}
	}
#pragma endregion




	void RgGUIContext::GUIRect(const RgVec2 & lp, const RgVec2 & sz, const RgVec4 & color)
	{
		//caculate group
		bool ingroup = UtilIsInGroup();
		if (ingroup == false) {
			_DrawRect(lp, sz, color, _GetDrawOrder());
		}
		else {
			auto& grouprect = m_state.GroupRectStack.top();
			RgVec4 contentrect(lp + grouprect.xy(), sz);
			bool iscliped = UtilClipRect(contentrect, grouprect);
			_DrawRect(contentrect.xy(), contentrect.zw(), color, _GetDrawOrder());
		}
	}

	void RgGUIContext::GUIGroupBegin(const RgVec2 & lp, const RgVec2 & sz)
	{
		_GroupBegin(lp, sz);
	}

	void RgGUIContext::GUIGroupEnd()
	{
		_GroupEnd();
	}


	RgImage * RgGUIContext::GetFontImage()
	{
		return m_pGlyph->GetImage();
	}


	RgGUIContext::RgGUIContext(const RgGUISettings & settings)
	{
		m_style = settings.Style;

		RgGUIContext();
	}

	RgGUIContext::RgGUIContext()
	{
		m_pGlyph = new RgGUIGlyph();

		m_pBufferIndices = new RgGUIIndicesBuffer();
		m_pBufferText = new RgGUIVertexBuffer();
		m_pBufferVertex = new RgGUIVertexBuffer();
	}

	RgGUIContext::~RgGUIContext()
	{
		Release();
	}


#pragma region state
	void RgGUIState::ongui(const RgWindowInput * input)
	{
		WindowGroupRect.z = input->WindowRect.z;
		WindowGroupRect.w = input->WindowRect.w;

		eventMouseLeftDown = input->LButton;
		eventMousePos = input->MousePos;
	}
	void RgGUIState::DrawOrderIncreae()
	{
		currentDrawOrder += 0.0001f;
	}

	void RgGUIState::ResetDrawOrder()
	{
		currentDrawOrder = 0.0f;
	}


#pragma endregion

#pragma region stateWindow
	RgGUIWindow * RgGUIStateWindow::GetWindow(long winid)
	{
		auto iter = windowMap.find(winid);
		if (iter == windowMap.end()) return nullptr;
		return (*iter).second;
	}
	void RgGUIStateWindow::DrawWindow(RgGUIWindow * window, RgGUIContext * ctx)
	{
		window->_buffer_vertex_begin = ctx->GetVertexBufferPtr()->GetVertexSize();

		//RgLogD() << "drawwindow" << window->title << window->_buffer_vertex_begin;
		window->_ondraw = true;
		stateWindowOrder = (float)window->order;

		auto& winrect = window->windowrect;
		auto& style = ctx->m_style;
		
		ctx->GUIGroupBegin(winrect.xy(), winrect.zw());

		//--------- begin window frame draw ---------//
		//Background
		ctx->GUIRect(RgVec2::Zero, winrect.zw(), window->windowColor);
		//Header
		ctx->GUIRect(RgVec2::Zero, RgVec2(winrect.z, style.WindowHeaderHeight),style.WindowHeaderColor);
		
		//content group
		ctx->GUIGroupBegin(RgVec2(0.0f, style.WindowHeaderHeight), RgVec2(winrect.z, winrect.w - style.WindowHeaderHeight));

		//--------- end window frame draw ---------//
	}
	void RgGUIStateWindow::DrawWindowEnd(RgGUIWindow * window, RgGUIContext * ctx)
	{
		ctx->GUIGroupEnd();		//end content group
		ctx->GUIGroupEnd();		//end window group

		window->_ondraw = false;
		window->_buffer_vertex_end = ctx->GetVertexBufferPtr()->GetVertexSize();
		//RgLogD() << "drawwindow end" << window->title << window->_buffer_vertex_end;
	}
	void RgGUIStateWindow::ongui(const RgGUIState & state,RgGUIContext * ctx)
	{
		//check whether to skip draw
		skipDraw = false;
		bool mousedown = state.eventMouseLeftDown;
		if (mousedown == false) {
			skipDraw = true;
			return;
		}

		//caculate focused window;
		RgGUIWindow * newfocusedWin = nullptr;
		long maxorder_focused = -1;		//maxorder of current mouseovered window
		long maxorder_window = -1;		//maxorder of all windows
		for (auto pair : windowMap) {
			auto win = pair.second;
			maxorder_window = (win->order > maxorder_window ? win->order : maxorder_window);
			if (win->windowrect.rect_contain(state.eventMousePos) == false) continue;
			if (win->order <= maxorder_focused) continue;
			maxorder_focused = win->order;
			win->_isfocused = true;
			if (newfocusedWin != nullptr) {
				newfocusedWin->_isfocused = false;
			}
			newfocusedWin = win;
		}

		if (newfocusedWin == nullptr) {
			if (windowFocused != nullptr) {
				windowFocused->_isfocused = false;
				windowFocused = nullptr;
			}
		}
		else {
			if (windowFocused != nullptr) {
				windowFocused->_isfocused = false;

				if (newfocusedWin->order < windowFocused->order) {
					newfocusedWin->order = windowFocused->order + 1;
				}
				windowFocused = newfocusedWin;
				windowFocused->_isfocused = true;
			}
			else
			{
				windowFocused = newfocusedWin;
				windowFocused->_isfocused = true;
				windowFocused->order = maxorder_window + 1;
			}
		}

		if (windowFocused == nullptr) {
			RgLogW() << "focused window null";
			return;
		}
		RgLogW() << ">> focused window:" << windowFocused->title;

		// every frame will draw focused window and new window
		// so remove lastfocusedWindows's buffer data and
		// set the PtrFloater to the end of the vertex buffer

		auto windowFocusedSize = windowFocused->_buffer_vertex_end - windowFocused->_buffer_vertex_begin;
		//RgLogW() << "focused window size" <<  windowFocusedSize;
		
		auto moveBufferOffset = ctx->GetVertexBufferPtr()->GetVertexSize() - windowFocused->_buffer_vertex_end;
		//RgLogW() << "move buffer offset" << moveBufferOffset << "|" << ctx->GetVertexBufferPtr()->GetVertexSize() << windowFocused->_buffer_vertex_end;

		if (moveBufferOffset == 0) {
			//no buffer move
			ctx->GetVertexBufferPtr()->ptrFloater -= windowFocusedSize;

			//RgLogD() << "buffersize" << ctx->GetVertexBufferPtr()->GetVertexSize();
			return;
		}

		auto movebufferBegin = ctx->GetVertexBufferPtr()->GetPtr() + windowFocused->_buffer_vertex_begin;
		auto movebufferEnd = ctx->GetVertexBufferPtr()->GetPtr() + windowFocused->_buffer_vertex_end;
		memmove(movebufferBegin, movebufferEnd, moveBufferOffset * sizeof(RgGUIVertex));

		//reset all window bufferpos
		for (auto pair : windowMap) {
			auto win = pair.second;
			if (win == nullptr) {
				RgLogE() << "window null";
				continue;
			}
			if (win->_buffer_vertex_begin > windowFocused->_buffer_text_end) {
				win->_buffer_vertex_begin -= windowFocusedSize;
				win->_buffer_vertex_end -= windowFocusedSize;

				//RgLogW() << "move window bufferpos" << win->title;
			}
		}
		ctx->GetVertexBufferPtr()->ptrFloater -= windowFocusedSize;

		RgLogD() << "buffersize" << ctx->GetVertexBufferPtr()->GetVertexSize();


	}

	void RgGUIStateWindow::endgui(const RgGUIState & state, RgGUIContext * ctx)
	{
		if (skipDraw) {
			return;
		}

		//for (auto pair : windowMap) {
		//	auto win = pair.second;
		//	RgLogD() << "order" << win->title << win->order;
		//}
	}

	void RgGUIStateWindow::register_win(RgGUIWindow* win)
	{
		if (win == nullptr) return;

		int ordernext = 0;

		if (windowMap.size() > 0) {
			auto iter = windowMap.end();
			iter--;
			ordernext = (*iter).second->order + 1;
		}
		win->order = ordernext;
		windowMap.insert(std::make_pair(win->winid, win));
	}

	bool RgGUIStateWindow::verify_valid(long winid)
	{
		if (skipDraw) return false;
		auto iter = windowMap.find(winid);
		if (iter == windowMap.end()) {
			RgLogE() << "window check focused error";
			return false;
		}
		return (*iter).second->_isfocused;
	}
#pragma endregion

	

}

