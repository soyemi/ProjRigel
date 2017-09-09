#pragma once
#include "rg_graphicsAPI.h"
#include <vector>
namespace rg {
	class RgShader;
	class RgBuffer;
	class RgRenderContext;

	class RgGraphicsContextDX11;

	enum class RgInputSlotClass
	{
		PER_VERTEX_DATA,
		PER_ELEMENT_DATA,
	};

	struct RgInputLayoutElement {
		const char* SemanticName = nullptr;
		unsigned int SemanticIndex = 0;
		RgGraphicsFormat Format = RgGraphicsFormat::UNKNOWN;
		unsigned int InputSlot = 0;
		RgInputSlotClass InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
		unsigned int AlignedByteOffset = 0;
	};

	class RgInputLayout {
		
	public:
		std::vector<RgInputLayoutElement> Elements;
		void * pLayout = nullptr;
	protected:
		RgInputLayout(const RgInputLayoutElement* elements, const unsigned size);
		virtual ~RgInputLayout();

		RgInputLayout(const RgInputLayout&) = delete;
		RgInputLayout& operator=(const RgInputLayout&) = delete;

		friend class RgGraphicsContextDX11;
	};
}