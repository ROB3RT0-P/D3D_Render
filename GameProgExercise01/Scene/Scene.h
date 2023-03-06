#pragma once

#include <Containers\List.h>

namespace scene
{
	class Camera;
	class TestObject;
	class Ground;
	class Flower;
	class Bee;
	class Wasp;

	// Object containing all the entities and related objects in the scene
	class Scene
	{
	public:
		static const UINT FlowerGridSize = 4;
		static const UINT BeeNum = 20;

		Scene();
		~Scene();

		void				Initialise();
		void				Shutdown();
		void				Update();
		void				Render();

		Flower* GetRandFlower();
		Wasp* GetRandWasp();

		inline Camera*		GetCamera() const
		{
			return m_camera;
		}

	private:
		//TestObject*			m_testObject1;
		//TestObject*			m_testObject2;
		Ground*				m_ground;
		Camera*				m_camera;
		Bee*				m_bee;
		Wasp*				m_wasp;
		
		containers::List<Bee*> m_beeList;
		containers::List<Flower*> m_flowerList;
	};
} // namespace scene