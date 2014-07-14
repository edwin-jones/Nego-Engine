#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();
	void Init(HINSTANCE hInstance, int width, int height);
	void Draw();
	void Dispose();
	void AddToScene(Model* modelToAdd);
	bool Update();
	Camera * Renderer::GetCamera();
	Vector4F Renderer::GetBackBufferColor();
	void Renderer::SetBackBufferColor(Vector4F newColor);
	bool Renderer::GetDisposedStatus();

private:
	void ConstructGLContext();
	void Render();
	void PreRenderSetup();
	int CheckMessages();
	const LPWSTR WindowName = L"Nego Engine";
};

