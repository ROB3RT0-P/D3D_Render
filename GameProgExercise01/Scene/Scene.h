#pragma once

class Ground;

class Scene
{
public:
	Scene();

	void			Initialise();
	void			Shutdown();

	void			Update();
	void			Render();

private:
	Ground*			m_ground;

	ID3D11Buffer* m_constantBuffer;
};
