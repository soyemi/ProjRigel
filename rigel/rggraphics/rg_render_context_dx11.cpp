#include "rggraphics.h"
#include "rg_render_context_dx11.h"
#include "rg_bufferDX11.h"
#include "rg_shaderDX11.h"
#include "rg_inputlayout.h"
#include "rg_command_list_dx11.h"
#include "rg_command_list.h"
#include "rg_buffer.h"
#include "rg_shader.h"
#include "rg_graphicsContextDX11.h"
namespace rg {
	void RgRenderContextDX11::InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage)
	{
		unsigned int stride = buffer->GetSettings().Stride;
		unsigned int offset = 0;

		auto bindtype = buffer->GetSettings().BindFlag;
		auto bufferdx11 = dynamic_cast<RgBufferDX11*>(buffer);
		switch (bindtype)
		{
		case rg::RgBufferBind::IndexBuffer:
			m_pDeviceContext->IASetIndexBuffer(bufferdx11->m_pbuffer, DXGI_FORMAT_R32_UINT, 0);

			RgLogW() << "set index buffer";
			break;
		case rg::RgBufferBind::VertexBuffer:
			m_pDeviceContext->IASetVertexBuffers(0, 1, &bufferdx11->m_pbuffer,&stride,&offset);
			RgLogW() << "set vertex buffer";
			break;
		case rg::RgBufferBind::ConstBuffer:
			if (((unsigned int)tarstage & (unsigned int)RgGraphicsPipelineStage::Vertex) != 0)m_pDeviceContext->VSSetConstantBuffers(0, 1, &bufferdx11->m_pbuffer);
			if (((unsigned int)tarstage & (unsigned int)RgGraphicsPipelineStage::Pixel) != 0)m_pDeviceContext->PSSetConstantBuffers(0, 1, &bufferdx11->m_pbuffer);
		default:
			break;
		}

		RgLogD() << "set buffer done!";
	}
	void RgRenderContextDX11::InputSetShader(std::shared_ptr<RgShader> shader)
	{
		RgShader * rgshader = shader.get();
		RgShaderDX11 * rgshaderdx11 = dynamic_cast<RgShaderDX11*>(rgshader);

		switch (shader->GetShaderEntry())
		{
		case RG_SHADER_ENTRY::Vertex:
			m_pDeviceContext->VSSetShader(rgshaderdx11->m_pVertexShader, nullptr, 0);
			RgLogW() << "set vertex shader";
			break;
		case RG_SHADER_ENTRY::Pixel:
			m_pDeviceContext->PSSetShader(rgshaderdx11->m_pPixelShader, nullptr, 0);
			RgLogW() << "set pixel shader";
		default:
			break;
		}
	}
	void RgRenderContextDX11::InputSetPrimitiveTopology()
	{
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	void RgRenderContextDX11::InputSetInputLayout(RgInputLayout * layout)
	{
		RG_ASSERT(layout);
		ID3D11InputLayout * dx11layout = (ID3D11InputLayout*)layout->pLayout;
		m_pDeviceContext->IASetInputLayout(dx11layout);
	}
	void RgRenderContextDX11::SetRenderTarget()
	{
		
	}
	void RgRenderContextDX11::SetViewPortDefault()
	{
		auto viewport = m_pGraphicsCtx->GetViewPort();
		m_pDeviceContext->RSSetViewports(1, &viewport);
	}
	void RgRenderContextDX11::SetRenderTargetDefault()
	{
		auto rtv = m_pGraphicsCtx->GetRenderTargetView();
		auto dsv = m_pGraphicsCtx->GetDepthStencilView();
		m_pDeviceContext->OMSetRenderTargets(1, &rtv, dsv);
	}
	void RgRenderContextDX11::SetDepthStencilStateDefault()
	{
		auto dss = m_pGraphicsCtx->GetDepthStencilState();
		m_pDeviceContext->OMSetDepthStencilState(dss, 1);
	}
	void RgRenderContextDX11::SetRasterizerStateDefault()
	{
		auto rs = m_pGraphicsCtx->GetRasterizerState();
		m_pDeviceContext->RSSetState(rs);
	}
	void RgRenderContextDX11::ClearRenderTarget(RgVec4 color)
	{
		auto rtv = m_pGraphicsCtx->GetRenderTargetView();
		const float c[4]{color.x,color.y,color.z,color.w};
		m_pDeviceContext->ClearRenderTargetView(rtv, c);
	}
	void RgRenderContextDX11::ClearDepthStencil()
	{
		auto dsv = m_pGraphicsCtx->GetDepthStencilView();
		m_pDeviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	void RgRenderContextDX11::DrawIndexed(unsigned int size)
	{
		m_pDeviceContext->DrawIndexed(size, 0, 0);
	}
	void RgRenderContextDX11::Draw()
	{
		m_pDeviceContext->DrawIndexed(3, 0, 0);
	}
	void RgRenderContextDX11::ClearState()
	{
		m_pDeviceContext->ClearState();
	}
	bool RgRenderContextDX11::FinishCommandList(bool restorectx, RgCommandList ** pcommandlist)
	{
		
		ID3D11CommandList * pcmdlist = nullptr;
		HRESULT hr = m_pDeviceContext->FinishCommandList(restorectx, &pcmdlist);
		if (hr != S_OK) {
			RgLogE() << "finish command list error"<<hr;
			return false;
		}
		RgCommandListDX11 * rgcmdlist = new RgCommandListDX11();
		rgcmdlist->m_pCommandList = pcmdlist;
		(*pcommandlist) = rgcmdlist;
		RgLogD() << "finish commandlist done!";
		return true;
	}
	void RgRenderContextDX11::ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx)
	{
		if (pcommandlist == nullptr || m_bIsImmediateContext == false) {
			RgLogW() << "skip exec command list";
		}
		RgCommandListDX11 *pcmdlistdx11 = dynamic_cast<RgCommandListDX11*>(pcommandlist);

		m_pDeviceContext->ExecuteCommandList(pcmdlistdx11->m_pCommandList, restorectx);

	}
	RgRenderContextDX11::RgRenderContextDX11(bool immedctx)
	{
		m_bIsImmediateContext = immedctx;
	}

	RgRenderContextDX11::~RgRenderContextDX11()
	{
		if (m_bIsImmediateContext == false) {
			m_pDeviceContext->Release();
			RgLogD() << "release deferred context";
		}
		m_pGraphicsCtx = nullptr;
		m_pDeviceContext = nullptr;
	}

}
