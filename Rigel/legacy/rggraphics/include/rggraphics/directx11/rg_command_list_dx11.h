#pragma once
#include "rg_command_list.h"
#include <d3d11.h>

namespace rg {

	class RgGraphicsContextDX11;


	class RgCommandListDX11 : public RgCommandList {

	public:
		void Release();
		~RgCommandListDX11();
	protected:
		RgCommandListDX11();
		

		RgCommandListDX11(const RgCommandListDX11&) = delete;
		RgCommandListDX11& operator=(const RgCommandListDX11&) = delete;


		ID3D11CommandList * m_pCommandList = nullptr;

	public:
		friend class RgRenderContextDX11;
	};
}