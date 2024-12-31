/*

I'm gonna be real with you, I have no real clue how this works, Folke did most of the heavy lifting in my original pong game and I just copied.
But hey, it works :)

ctrl + f and search "movement" to see all the stuff you need to add

*/
#include "stdafx.h"
#include "GameWorld.h"

void Go(void);

int main(const int /*argc*/, const char* /*argc*/[])
{
	Go();
	return 0;
}

Tga::InputManager* SInputManager; // MOVEMENT 1

LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	SInputManager->UpdateEvents(message, wParam, lParam); // MOVEMENT 2

	return 0;
}


void Go()
{
	Tga::LoadSettings(TGE_PROJECT_SETTINGS_FILE);

	Tga::EngineConfiguration winconf;

	winconf.myApplicationName = L"TGE - Amazing Game";
	winconf.myWinProcCallback = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
#ifdef _DEBUG
	winconf.myActivateDebugSystems = Tga::DebugFeature::Fps | Tga::DebugFeature::Mem | Tga::DebugFeature::Filewatcher | Tga::DebugFeature::Cpu | Tga::DebugFeature::Drawcalls | Tga::DebugFeature::OptimizeWarnings;
#else
	winconf.myActivateDebugSystems = Tga::DebugFeature::Filewatcher;
#endif

	if (!Tga::Engine::Start(winconf))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return;
	}

	{
		SInputManager = new Tga::InputManager(*Tga::Engine::GetInstance()->GetHWND()); // MOVEMENT 3

		GameWorld gameWorld;
		gameWorld.Init(SInputManager); // MOVEMENT 4

		Tga::Engine& engine = *Tga::Engine::GetInstance();

		while (engine.BeginFrame()) {
			SInputManager->Update(); // MOVEMENT 5
			gameWorld.Update(engine.GetDeltaTime());
			gameWorld.Render();

			engine.EndFrame();
		}
	}

	Tga::Engine::GetInstance()->Shutdown();
}

