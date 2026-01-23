#pragma once


// add ifdef for windows and macos

extern Acorn::Application* Acorn::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Acorn {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Acorn::Application* app = Acorn::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef AC_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Acorn::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Acorn::Main(argc, argv);
}

#endif // AC_DIST

