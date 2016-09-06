/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
   (c) Charles Petzold, 1998
   ------------------------------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//��Ϊ��WinMain�����о�Ҫ�õ�������Ҫ������

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)//�������ʼ��������ʾ������С���������ʾ
{
	static TCHAR szAppName[] = TEXT("HelloWin");

	HWND         hwnd;
	MSG          msg;

	WNDCLASS     wndclass;//����һ��WNDCLASS������

	//��������ʼ���ô�����
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//���ڷ��
	//����������ʾˮƽ��ֱ�ı�ʱ�������ػ�
	wndclass.lpfnWndProc = WndProc;//���ڸô���������д��ڵĴ��ڹ��̵ĵ�ַ
	wndclass.cbClsExtra = 0;//����������������Ԥ������ռ�
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;//Ӧ�ó����ʵ�����(WinMain��һ������)
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//�����л��ڸ�
	//������Ĵ����趨һ��ͼ��,��Ҫ�����Զ���ͼ�꣬���һ������ΪӦ�ó���ʵ�����hInstance
	//���ڶ�������ʼ��Ϊһ��ǰ׺Ϊ"IDI_"��ͼ���ʶ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//���ƣ��������
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����ɫ
	wndclass.lpszMenuName = NULL;//�˵���
	wndclass.lpszClassName = szAppName;//����������

	//���WNDCLASS�ṹ�ĳ�ʼ���󣬵���RegisterClass���������д�����ע��
	//ע�⣬Ҫ����ȡ��ַ��(�����Ǳ�׼�Ĵ�������ע�⣬ע��ʧ��Ҫ��ʱ�˳�)
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	//�������ֻ��ע�ᴰ���࣬�������������������
	//����һ�����ڵľ��������ֵ������HWND���͵ı�����
	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("The Hello Program"), // window ����
		WS_OVERLAPPEDWINDOW,        // ���ڷ����������ͨ�������
		CW_USEDEFAULT,              // initial x position
		CW_USEDEFAULT,              // initial y position
		CW_USEDEFAULT,              // initial x size
		CW_USEDEFAULT,              // initial y size
		NULL,                       // ������ handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // ��������

	////������ǰѴ���������ʾ����
	ShowWindow(hwnd, iCmdShow);//iCmdShow(WinMain����)
	//�������ʼ��������ʾ������С���������ʾ
	UpdateWindow(hwnd);//��������򴰿ڹ��̺���(WndProc)����һ��WM_PAINT��Ϣ

	//WindowsΪÿ������ά����һ����Ϣ���У����¼������󣬻��Զ����¼�ת��Ϊ��Ϣ
	//�������ڳ������Ϣ�����У�����ͨ���������Ϣѭ��������Ϣ�����л�ȡ��Ϣ
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage()����Ϣ�����м�����Ϣ
	{					//����������ΪNULL/0��ʾ�õ��ó��򴴽������д��ڵ���Ϣ
		//���õ�����ϢΪWM_QUIT����GetMessage()����0�����򷵻ط�0

		TranslateMessage(&msg);//���ظ�Windows�Խ���ĳЩ������Ϣ��ת��

		DispatchMessage(&msg);//�ٴν���Ϣ���ظ�Windows
	}
	return msg.wParam;
}


//����������������ڴ��ڹ����У�(���ڹ��̺�����������)
//һ��������԰���������ڹ��̣���һ�����ڹ�������һ������RegisterClass�Ĵ��������
//���ڹ��̺���ֻ������������Ϣ�������������Ϣ������CREATE��PAINT��Ϣ��
LRESULT CALLBACK WndProc(HWND hwnd,   //���ھ��
	UINT message,  //��Ϣ��־
	WPARAM wParam, //���������������ṩ��Ϣ���ḻ����Ϣ
	LPARAM lParam)
{
	//�������������洦����ϢҪ��
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	switch (message)
	{
	case WM_CREATE:
		PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;//ע�⣬��Ϣ�������return 0��������break

	case WM_PAINT://�����������ʼ��/���ĳߴ�/��С��...������Чʱ���ػ洰��
		hdc = BeginPaint(hwnd, &ps);//�����豸�������

		GetClientRect(hwnd, &rect);//�õ����ڵ�(legt,top,right,bottom)��Ϣ��
									//������rect�ṹ��
		
		//����rect�ṹ���е���Ϣ�������ı�
		DrawText(hdc,		//�豸�������
				TEXT("Hello, Windows 98!"), //�ı���Ϣ
				-1, //��ʾ���ı��ַ�����0��β
				&rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);//��ʾ��ʽ�����У����У�ˮƽ

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY://����˹ر�(���ٴ���)
		PostQuitMessage(0);
		return 0;
	}

	//һ����������ʽ����
	return DefWindowProc(hwnd, message, wParam, lParam);
}