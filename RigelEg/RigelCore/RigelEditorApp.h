#pragma once
#include "Stdafx.h"
#include "cRigelEditorApp.h"

namespace RigelCore
{
	class cRigelEditorApp;

	public ref class RigelEditorApp
	{
	public:
		delegate void DelEvent();
		event DelEvent ^delOnGUI;

	private:
		cRigelEditorApp *_app;

	public:
		RigelEditorApp();
		~RigelEditorApp();

		void Run();
		void onWindowDestroy();

		void callbackOnGUI();

		void ProjectOpen(System::String ^projFile);
		void ProjectClose();
		void ProjectSave();
	};

}

