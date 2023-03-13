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

		Scene();
		~Scene();

		void				Initialise();
		void				Shutdown();
		void				Update();
		void				Render();
		void				AdjustBeeNum( int AdjustedBeeNum );
		void				AdjustBeeTimer( int AdjutedBeeTimer);

		Flower*				GetRandFlower();
		Wasp*				GetWaspClosestToEntity( const Entity* const entity );
		Bee*				GetBeeClosestToFlower( const Flower* const flower );
		Flower*				GetHighestNectarFlower();
		

		inline Camera*		GetCamera() const
		{
			return m_camera;
		}

		int				GetBeeNum()
		{
			return m_beeNum;
		}

		float				GetBeeTimer()
		{
			return m_beeTimer;
		}

	private:
		float				m_waspTimer;
		float				m_beeTimer;
		float				m_beeTimerReset;
		float				m_waspTimerReset;
		UINT				m_beeNum = 1;
		Ground*				m_ground;
		Camera*				m_camera;


		containers::List<Bee*> m_beeList;
		containers::List<Flower*> m_flowerList;
		containers::List<Wasp*> m_waspList;
	};
} // namespace scene