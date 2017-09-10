#pragma once
#include <memory>

namespace rg {

	class RgGraphicsContext;
	class RgBuffer;
	class RgShader;
	class RgMaterial;
	class RgInputLayout;
	class RgCommandList;

	class RgRenderContext {

	protected:
		RgRenderContext();
		virtual ~RgRenderContext();

		RgRenderContext(const RgRenderContext&) = delete;
		RgRenderContext& operator=(const RgRenderContext&) = delete;


	public:
		virtual void InputSetBuffer(RgBuffer* buffer, unsigned int tarstage = 0);
		virtual void InputSetMaterial(std::shared_ptr<RgMaterial> material);
		virtual void InputSetShader(std::shared_ptr<RgShader> shader);
		virtual void InputSetPrimitiveTopology();
		virtual void InputSetInputLayout(RgInputLayout * layout);

		virtual void DrawIndexed(unsigned int size);
		virtual void Draw();


		virtual void ClearState();
		virtual bool FinishCommandList(bool restorectx, RgCommandList ** pcommandlist);
		virtual void ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx);
	public:
		friend class RgGraphicsContext;
	};
}