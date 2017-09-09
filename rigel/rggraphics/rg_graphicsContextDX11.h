#pragma once
#include "rg_graphicscontext.h"

#include <rgcore\rgcore.h>

#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")


namespace rg {


	class RgGraphicsContextDX11 : public RgGraphicsContext
	{
	protected:
		RgGraphicsContextDX11();
		~RgGraphicsContextDX11();

		void init(RG_GRAPHICS_INIT_SETTINGS *settings);
		void release();

		void DrawSetBuffer(std::shared_ptr<RgBuffer> buffer);
		void DrawSetMaterial(std::shared_ptr<RgMaterial> material);
		void DrawSetShader(std::shared_ptr<RgShader> shader);
		void DrawSetPrimitiveTopology();
		void DrawIndexed(unsigned int size);

	public:
		std::shared_ptr<RgShader> CompileShaderFromFile(std::wstring filepath, RgShaderOptions& options);
		virtual std::shared_ptr<RgBuffer> CreateBuffer(RgBufferSettings settings);
		RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements,const unsigned int size);

		void resizeBuffer(unsigned int width, unsigned int height);
		void render();


	private:
		

		ID3D11Device *m_pD3D11Device = nullptr;
		ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
		IDXGISwapChain * m_pSwapChain = nullptr;
		
		ID3D11Texture2D * m_depthStencilBuffer = nullptr;
		ID3D11DepthStencilState *m_pdepthStencilState = nullptr;
		ID3D11DepthStencilView *m_pdepthStencilView = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
		ID3D11RasterizerState* m_pRasterizerState = nullptr;

		HRESULT createDeviceAndContext();
		void releaseDeviceAndContext();
		HRESULT createSwapChain();
		void releaseSwapChain();

		HRESULT createRenderTarget();
		HRESULT clearRenderTarget();


	public:
		friend class RgGraphicsAPI;

	};
}