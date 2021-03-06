#pragma once
#include <string>
#include <rgcore\rg_image.h>
#include <rgcore\rg_font.h>
#include <map>
namespace rg {

	class RgGUIGlyph {
	public:
		RgGUIGlyph(std::wstring fontpath);
		RgGUIGlyph();
		~RgGUIGlyph();
		void Release();
		bool IsValid() const;

		RgImage* GetImage();

		void SetCharUV(const char c, RgVec2& uv, unsigned int vi) const;
		const RgVec2& GetCharUV(const char c, unsigned int vi) const;
		const RgVec2& GetCharPos(const char c, unsigned int vi) const;

		float GetTextWidth(std::string str) const;
	private:
		RgGUIGlyph(const RgGUIGlyph&) = delete;
		RgGUIGlyph& operator=(const RgGUIGlyph&) = delete;

		void GenFontImage();
		void GenCharUV();
		void GenCharPos();

		bool m_bIsValid = false;
		RgFont * m_pfont = nullptr;
		RgImage * m_pimg = nullptr;
		RgVec4 m_charrect[128];
		RgVec2 m_charuv[512];
		RgVec2 m_charpos[512];
	};
}