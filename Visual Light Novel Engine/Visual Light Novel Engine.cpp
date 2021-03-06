#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));

	Setting setting;

	setting.AppName = "Visual Light Novel";
	setting.WindowInstance = hInstance;
	setting.WindowHandle = nullptr;
	setting.FOV = 0;
	setting.Width = 1280;
	setting.Height = 720;
	setting.IsOrtho = true;
	setting.IsVSync = false;
	setting.IsFullScreen = false;
	setting.IsMenu = true;

	SETTING->AddWindow("Game", setting);

	setting.AppName = "Menu";
	setting.Width = 160;
	setting.Height = 360;
	setting.IsMenu = false;

	SETTING->AddWindow("Menu", setting);

	setting.AppName = "Tool";
	setting.Width = 250;
	setting.Height = 100;
	setting.IsMenu = false;

	SETTING->AddWindow("Tool", setting);

	setting.AppName = "Select Info";
	setting.Width = 250;
	setting.Height = 220;
	setting.IsMenu = false;

	SETTING->AddWindow("Info", setting);

	setting.AppName = "Hierarchy";
	setting.Width = 250;
	setting.Height = 720;
	setting.IsMenu = false;

	SETTING->AddWindow("Hierarchy", setting);

	setting.AppName = "Blueprint";
	setting.Width = 1280;
	setting.Height = 720;
	setting.IsMenu = false;

	SETTING->AddWindow("Blueprint", setting);

	Window * window = new Window();
	window->Run();

	SAFE_DELETE(window);
}