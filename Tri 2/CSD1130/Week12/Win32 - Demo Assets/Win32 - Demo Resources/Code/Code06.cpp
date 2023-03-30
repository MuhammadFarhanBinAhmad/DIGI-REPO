// Main message loop:
bool loop = true;
while(loop)
{
	//while (GetMessage(&msg, NULL, 0, 0))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			loop = false;

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}		
	}
	static int counterLoop;
	if(counterLoop < 100000)
		counterLoop++;
	printf("counterLoop = %d\n", counterLoop);
}