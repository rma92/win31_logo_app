#include <windows.h>
#include "res.h"

HENHMETAFILE hemf;
HMETAFILE hmf;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  HANDLE hres;
  PAINTSTRUCT ps;
  RECT rct;
  DWORD dw;
  HRSRC hrsrc;
  HBRUSH hbr;
  HDC hdcMeta;
  static char buff[255];
  switch(message)
  {
    case WM_CREATE:
    { 

      hrsrc = FindResource( GetModuleHandle( NULL ),MAKEINTRESOURCE(ID_MF1), "METAFILE"); 
      hres = LoadResource( GetModuleHandle( NULL ), hrsrc);
      dw = SizeofResource( GetModuleHandle( NULL ), hrsrc);

      hmf = SetMetaFileBitsEx( dw, hres );
    }
    break;
    case WM_PAINT:
      hdc = BeginPaint( hWnd, &ps );
      hbr = CreateSolidBrush( RGB( 255,255,255 ) );

      //Logo
      GetClientRect( hWnd, &rct );
      FillRect( hdc, &rct, hbr );
      SetMapMode( hdc, MM_ANISOTROPIC);
      SetViewportExtEx( hdc, rct.right >> 1, rct.bottom >> 1, NULL );
      SetViewportOrgEx( hdc, 10, 10, NULL );
      PlayMetaFile( hdc, hmf );
      DeleteObject( hbr );
      
      SetViewportOrgEx( hdc, 0, 0, NULL );
      SetViewportExtEx( hdc, rct.right, rct.bottom, NULL);

      //Text1
      rct.left = 400;
      rct.top = 10;
      rct.right = 600;
      rct.bottom = 30;
      DrawText( hdc, Name1, -1, &rct, 0 );

      //Text2
      rct.left = 400;
      rct.top = 30;
      rct.right = 600;
      rct.bottom = 50;
      DrawText( hdc, Name2, -1, &rct, 0 );

      rct.top = 0;
      rct.left = 0;
      rct.bottom = 5;
      rct.right = 20;
      hbr = CreateSolidBrush( RGB( 0,5,255 ) );
      FillRect( hdc, &rct, hbr );
      DeleteObject( hbr );
      EndPaint( hWnd, &ps );
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg1;
  WNDCLASS wc1;
  HWND hWnd1;
  ZeroMemory(&wc1, sizeof wc1);
  wc1.hInstance = hInst;
  wc1.lpszClassName = AppName;
  wc1.lpfnWndProc = (WNDPROC)WndProc;
  wc1.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
  //wc1.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
  //wc1.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc1.hCursor = LoadCursor(NULL, IDC_ARROW);
  if(RegisterClass(&wc1) == FALSE) return 0;
  hWnd1 = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 360, 240, 0, 0, hInst, 0);
  if(hWnd1 == NULL) return 0;
  while(GetMessage(&msg1,NULL,0,0) > 0){
    TranslateMessage(&msg1);
    DispatchMessage(&msg1);
  }
  return msg1.wParam;
}
