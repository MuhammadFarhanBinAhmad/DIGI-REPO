GetClientRect(hWnd, &rect);
for (x = 0; x < rect.right; x += 100)
{
	MoveToEx(hdc, x, 0, NULL);
	LineTo(hdc, x, rect.bottom);
}

for (y = 0; y < rect.bottom; y += 100)
{
	MoveToEx(hdc, 0, y, NULL);
	LineTo(hdc, rect.right, y);
}

MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
PolylineTo(hdc, pt + 1, 5);

for (j = 0; j < 5; j++)
{
	rect2.top = j * 100;
	rect2.left = j * 100;
	rect2.bottom = (j + 1) * 100;
	rect2.right = (j + 1) * 100;

	FillRect(hdc, &rect2, CreateSolidBrush(RGB(20 * (j + 1), 40 * (j + 1), 53 * (j + 1))));
}


//Declare the following before the switch statement
//We need to declare the following:
int x, y;
int j;
POINT pt[6] = { 460, 150, 500, 150, 530, 104, 700, 290, 790, 300, 460, 150 };
RECT rect, rect2;