#pragma once

#include <Containers\List.h>

namespace scene
{
class Camera;
class TestObject;
class Ground;
class Flower;
class Bee;

// Object containing all the entities and related objects in the scene
class Scene
{
public:
	static const UINT FlowerGridSize = 4;
	Scene();
	~Scene();

	void				Initialise();
	void				Shutdown();

	void				Update();
	void				Render();

	Flower* GetFlower();

	inline Camera*		GetCamera() const
	{
		return m_camera;
	}


private:
	TestObject*			m_testObject1;
	TestObject*			m_testObject2;
	Ground*				m_ground;
	Camera*				m_camera;
	Bee*				m_bee;

	containers::List<Flower*> m_flowerList;
};

} // namespace scene