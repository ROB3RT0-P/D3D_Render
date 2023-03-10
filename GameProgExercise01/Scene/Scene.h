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
	class Entity;

	// Object containing all the entities and related objects in the scene
	class Scene
	{
	public:
		static const UINT FlowerGridSize = 4;
		UINT BeeNum = 1;
		float BeeTimer = 5.0f;

		Scene();
		~Scene();

		void				Initialise();
		void				Shutdown();
		void				Update();
		void				Render();
		void				AdjustBeeNum( int AdjustedBeeNum );
		void				AdjustBeeTimer( int AdjutedBeeTimer);

		Flower*				GetRandFlower();
		Wasp*				GetWasps();
		Wasp*				GetWaspClosestToEntity( const Entity* const entity );
		Bee*				GetBeeClosestToFlower( const Flower* const flower );
		Flower*				GetHighestNectarFlower();
		

		inline Camera*		GetCamera() const
		{
			return m_camera;
		}

		int				GetBeeNum()
		{
			return BeeNum;
		}

		float				GetBeeTimer()
		{
			return BeeTimer;
		}

	private:
		float				m_beeTimer;
		float				m_waspTimer;
		float				m_initBeeTimer;
		float				m_initWaspTimer;
		Ground*				m_ground;
		Camera*				m_camera;

		containers::List<Bee*> m_beeList;
		containers::List<Flower*> m_flowerList;
		containers::List<Wasp*> m_waspList;
	};
} // namespace scene