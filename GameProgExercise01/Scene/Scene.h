#pragma once

namespace scene
{
class Camera;

class TestObject;
class Ground;

// Object containing all the entities and related objects in the scene
class Scene
{
public:
	Scene();
	~Scene();

	void				Initialise();
	void				Shutdown();

	void				Update();
	void				Render();

	inline Camera*		GetCamera() const
	{
		return m_camera;
	}

private:
	TestObject*			m_testObject1;
	TestObject*			m_testObject2;
	Ground*				m_ground;
	Camera*				m_camera;
};

} // namespace scene