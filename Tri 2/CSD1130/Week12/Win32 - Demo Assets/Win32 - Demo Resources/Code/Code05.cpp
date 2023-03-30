if(AllocConsole())
{		
	FILE* file;
	
	freopen_s(&file, "CONOUT$", "wt", stdout);
	freopen_s(&file, "CONOUT$", "wt", stderr);
	freopen_s(&file, "CONOUT$", "wt", stdin);

	SetConsoleTitle(L"Simulation...");

	printf("Simulation Starting...\n");
}