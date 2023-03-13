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
		static const int SpawnMax;
		static const float TimerMax;
		static const float TimerCheck; // Check if timer is below certain amount.

		Scene();
		~Scene();

		void				Initialise();
		void				Shutdown();
		void				Update();
		void				Render();
		void				AdjustSpawnAmount( int adjustedBeeNum );
		void				AdjustBeeTimer( float adjutedBeeTimer);

		Flower*				GetRandFlower();
		Wasp*				GetWaspClosestToEntity( const Entity* const entity );
		Bee*				GetBeeClosestToFlower( const Flower* const flower );
		Flower*				GetHighestNectarFlower();
		

		inline Camera*		GetCamera() const
		{
			return m_camera;
		}

		int				GetSpawnAmount()
		{
			return m_spawnAmount;
		}

		float				GetBeeTimer()
		{
			return m_beeTimerReset;
		}

	private:
		float				m_waspTimer;
		float				m_beeTimer;
		float				m_beeTimerReset;
		float				m_waspTimerReset;
		UINT				m_spawnAmount;

		Ground*				m_ground;
		Camera*				m_camera;


		containers::List<Bee*> m_beeList;
		containers::List<Flower*> m_flowerList;
		containers::List<Wasp*> m_waspList;
	};
} // namespace scene