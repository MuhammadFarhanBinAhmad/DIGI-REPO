RECT rect;
GetWindowRect(hWnd, &rect);
SetWindowPos(hDlg, 0, rect.left + 100, rect.top + 100, 322, 200, SWP_SHOWWINDOW);