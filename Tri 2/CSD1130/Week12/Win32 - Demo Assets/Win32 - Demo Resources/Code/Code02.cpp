HBITMAP hBtp;//add this at the beginning before the switch case
case WM_CREATE:
		hBtp = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (ULONG_PTR)CreatePatternBrush(hBtp));
		break;