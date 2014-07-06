#include "stdafx.h"
#include "Renderer.h"
#include "Input.h"

GLfloat * VertexList;
GLushort * Indices;
GLfloat * Colors;
GLfloat * TexturePositions;

vector<Model*> ModelsToDraw;

//global variables
WNDCLASS wc;
HWND hWnd;
HDC hDC;
HGLRC hRC;
MSG msg;
HICON hicon;
GLuint currentTexture;

Camera * CurrentCamera;
Vector4F BackBufferColor;

Vector2I CurrentScreenSize;

bool Disposed = false;


Renderer::Renderer()
{
	
}


Renderer::~Renderer()
{
	Dispose();
}

void Renderer::AddToScene(Model* modelToAdd)
{
	ModelsToDraw.push_back(modelToAdd);
}

Camera * Renderer::GetCamera()
{
	return CurrentCamera;
}

bool Renderer::GetDisposedStatus()
{
	return Disposed;
}

Vector4F Renderer::GetBackBufferColor()
{
	return BackBufferColor;
}

void Renderer::SetBackBufferColor(Vector4F newColor)
{
	BackBufferColor = Vector4F(newColor);

	//tell open gl client buffer WHAT the back buffer color SHOULD be (when gl clear is called)
	glClearColor(BackBufferColor.X, BackBufferColor.Y, BackBufferColor.Z, BackBufferColor.W);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)	{
	case WM_CREATE:
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		return 0;
	case WM_KEYUP:
	{
		//Record what key was released.
        Input::SetKeyState(wParam, false);

		return 0;
	}

	case WM_KEYDOWN:
	{
		//record what key was pressed
		Input::SetKeyState(wParam, true);

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void Renderer::Init(HINSTANCE hInstance, int width, int height)
{
	BackBufferColor = Vector4F(0,0,0,1.0f);

	CurrentCamera = new Camera();

	CurrentScreenSize = Vector2I(height, width);

	VertexList = new GLfloat[200000];
	Indices = new GLushort[200000];
	Colors = new GLfloat[200000];
	TexturePositions = new GLfloat[200000];

	//load custom window icon.
	hicon = (HICON)LoadImage(GetModuleHandle(NULL), L"cubes.ico", IMAGE_ICON,
		0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = hicon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GLSample";
	RegisterClass(&wc);

	hWnd = CreateWindow(L"GLSample", L"Edwin's OpenGL Sample Program", WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0, 0, CurrentScreenSize.X, CurrentScreenSize.Y, NULL, NULL, hInstance, NULL);
	hDC = GetDC(hWnd);

	ConstructGLContext();

	wglMakeCurrent(NULL, NULL);

	wglMakeCurrent(hDC, hRC);

	glewInit();

	PreRenderSetup();

	//load texture

	Bitmap * bmp = new Bitmap("Temp.bmp");

	glGenTextures(1, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->GetWidth(), bmp->GetHeight(),
		0, GL_RGB, GL_UNSIGNED_BYTE, bmp->GetData());

	//

}

void Renderer::Draw()
{
	CurrentCamera->Apply();
	Render();
}


void Renderer::Dispose()
{
	if (!Disposed)
	{
		delete[] VertexList;
		delete[] Indices;
		delete[] Colors;

		for (int i = 0; i < ModelsToDraw.size(); i++)
		{
			delete ModelsToDraw[i];
		}


		delete CurrentCamera;
	}

	Disposed = true;
}

void Renderer::ConstructGLContext()
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iFormat, &pfd);

	// create and enable the render context (RC)
	hRC = wglCreateContext(hDC);
}

void Renderer::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	int vertexArraystep = 0;
	int indexArraystep = 0;
	int colourArraystep = 0;
	int texturePositionArrayStep = 0;

	for (int x = 0; x < ModelsToDraw.size(); x++)
	{
		ModelsToDraw[x]->PopulateGraphicsArray(VertexList, &vertexArraystep, Indices, &indexArraystep, Colors, &colourArraystep, TexturePositions, &texturePositionArrayStep);
	}


	//
	glVertexPointer(3, GL_FLOAT, 0, VertexList);
	glColorPointer(3, GL_FLOAT, 0, Colors);
	glTexCoordPointer(2, GL_FLOAT, 0, TexturePositions);

	glClear(GL_DEPTH_BUFFER_BIT);
	if (!Input::IsKeyDown(VK_SPACE))glClear(GL_COLOR_BUFFER_BIT);

	//draw 18 verts / 6 triangle(s) per tim0
	glDrawElements(GL_TRIANGLES, ModelsToDraw.size() * 36, GL_UNSIGNED_SHORT, Indices);


	glFinish();
	SwapBuffers(hDC);
}

void Renderer::PreRenderSetup()
{
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, CurrentScreenSize.X, CurrentScreenSize.Y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, CurrentScreenSize.X / (double)CurrentScreenSize.Y, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);
}


//returns 1 while not quitting, returns 0 when WM_QUIT is found in the window message queue.
bool Renderer::Update()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// handle or dispatch messages
		if (msg.message == WM_QUIT)
		{
			PostQuitMessage(0);
			Dispose();
			return false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return true;
}