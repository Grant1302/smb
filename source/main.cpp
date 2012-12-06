/*
 * main.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Anton L.
 */

#ifdef WIN32
#include <windows.h>
#endif
#include "CApp.h"

#ifdef WIN32
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
	CApp app;

	return app.OnExecute();
}
