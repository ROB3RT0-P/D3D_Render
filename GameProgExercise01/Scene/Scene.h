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
		static const UINT BeeNum = 40;
		static const UINT WaspNum = 2;

		Scene();
		~Scene();

		void				Initialise();
		void				Shutdown();
		void				Update();
		void				Render();

		Flower* GetRandFlower();
		Wasp* GetWasps();
		//Wasp* GetWaspClosestToEntity(const Entity* const entity);

		inline Camera*		GetCamera() const
		{
			return m_camera;
		}

	private:
		Ground*				m_ground;
		Camera*				m_camera;

		containers::List<Bee*> m_beeList;
		containers::List<Flower*> m_flowerList;
		containers::List<Wasp*> m_waspList;
	};
} // namespace scene