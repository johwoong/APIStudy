#include "global.h".h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL
// 지역변수 앞에 그변수의 의미를 담음 _In , In_opt 의미가 없다는 의미 >>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  // 실행된 프로세스의 시작 주소
	_In_opt_ HINSTANCE hPrevInstance, // 이전 프로세스의 시작 주소 - 초창기의 윈도우
	_In_ LPWSTR    lpCmdLine, // 문자열 주소를 받음
	_In_ int       nCmdShow)
{
	// 메모리 릭(누수) 체크
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(273);

	UNREFERENCED_PARAMETER(hPrevInstance); // 참조되지 않는 변수라는걸 알려주는거임.. 의미없음 - 주석
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

	// 윈도우 정보 등록
	MyRegisterClass(hInstance);

	// 윈도우 생성 - 유저와 프로그램 간의 인터페이스
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Core 초기화
	if ((CCore::GetInst()->Init(g_hWnd, POINT{ 1280, 768 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
		return FALSE;
	}

	// 단축키 테이블 정보 로딩
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg; // 발생한 메시지를 여기에 채움

	//SetTimer(g_hWnd, 10, 0, nullptr);
	// GetMessage
	// 메시지큐에서 메시지 확인될때까지 대기
	// GetMessage가 false를 반환하면 프로그램 종료
	// GetMessage에서의 메시지가 어떤 메서드인지에 따라서 true false를 반환
	//
	// 기본 메시지 루프입니다:

	// Peek Message
	// 메서지 유무와 관계없이 반환
	// 메시지가 있었으면 true 없었으면 false를 반환??
	// 메시지큐에서 메시지를 확인한 경우 true, 메시지큐에서 메시지가 없는 경우 false를 반환
	// 프로그램이 메시지에만 의존 GetMessage때문에
	while (true) // 메시지 큐에서 꺼내와서
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // hwnd 메시지가 발생한 윈도우, // 단축키 관련 메시지인지 확인
			{
				// 받아온 메시지 처리
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// 메시지가 발생하지 않는 대부분의 시간
		else
		{
			// Game 코드 수행
			// 디자인 패턴(설계 유형)
			// 싱글톤 패턴
			CCore::GetInst()->Update();
		}
	}

	return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#include <vector>
using std::vector;
struct tObjInfo
{
	POINT g_tObjectPos;
	POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

// 좌 상단
POINT g_ptLT;
// 우 하단
POINT g_ptRB;

bool bLbtnDown = false;

INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{ // 프로그래머가 커스텀해서 작성
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_MENU_TITLE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // 언제 발생하느냐?? 윈도우에 무효화(Invalidate)영역이 발생한 경우
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps); // 그리기 시작 알림
		// DC를 얻어옴
		//Rectangle(hdc, 1180, 668, 1280, 768);

		// 그리기 종료 알림
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			//g_tObjectPos.y -= 10; // 10픽셀단위로 위로
			//InvalidateRect(hWnd, nullptr, true); // 무효화 영역을 직접 설정 // 2번째 인자 : nullptr 전체 , 3번째 인자 지웠다가 다시그리기
			break;
		case VK_DOWN:
			//g_tObjectPos.y += 10; // 10픽셀단위로 위로
			//InvalidateRect(hWnd, nullptr, true); // 무효화 영역을 직접 설정 // 2번째 인자 : nullptr 전체 , 3번째 인자 지웠다가 다시그리기
			break;
		case VK_LEFT:
			//g_tObjectPos.x -= 10; // 10픽셀단위로 위로
			//InvalidateRect(hWnd, nullptr, true); // 무효화 영역을 직접 설정 // 2번째 인자 : nullptr 전체 , 3번째 인자 지웠다가 다시그리기
			break;
		case VK_RIGHT:
			//g_tObjectPos.x += 10; // 10픽셀단위로 위로
			//InvalidateRect(hWnd, nullptr, true); // 무효화 영역을 직접 설정 // 2번째 인자 : nullptr 전체 , 3번째 인자 지웠다가 다시그리기
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		// 마우스 위치 찍기
		g_ptLT.x = LOWORD(lParam); // 하위 바이트 // 가로
		g_ptLT.y = HIWORD(lParam); // 상위 바이트 // 세로
		bLbtnDown = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		g_ptRB.x = LOWORD(lParam);
		g_ptRB.y = HIWORD(lParam);

		tObjInfo info = {};
		info.g_tObjectPos.x = (g_ptLT.x + g_ptRB.x) / 2;
		info.g_tObjectPos.y = (g_ptLT.y + g_ptRB.y) / 2;

		info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
		info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

		g_vecInfo.push_back(info);

		bLbtnDown = false;
		InvalidateRect(hWnd, nullptr, true);
		break;
	}
	case WM_MOUSEMOVE:
		if (bLbtnDown)
		{
			g_ptRB.x = LOWORD(lParam);
			g_ptRB.y = HIWORD(lParam);
			InvalidateRect(hWnd, nullptr, true);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//case WM_TIMER:
		//{
		//    int a = 0;
		//}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // 그외의 코드는 모두처리 // 기본 프로세스
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}