#pragma once


namespace rg {
	class RgCommandList {
	protected:
		RgCommandList();
	public:
		virtual ~RgCommandList();

	public:
		virtual void Release();
	};
}