#include "stdafx.h"
#include "Main.h"


int main(int argc, char *argv[])
{
	Main* cmain = new Main(600,400);
	cmain->GameLoop();
	delete cmain;
	return 0;
}

