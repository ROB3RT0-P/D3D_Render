#include "GameProgExercise01.h"
#include "DX\DeviceResources.h"
#include "Core.h"
#include "Utils\File.h"
#include "Scene\Scene.h"
#include "Scene\Entities\TestObject.h"
#include "Scene\Entities\Ground.h"
#include "Scene\Camera.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Bee.h"
#include "Scene\Entities\Wasp.h"
#include "Utils\Maths.h"
#include "Utils\Timers.h"

using namespace DirectX;

namespace scene
{
	const int Scene::SpawnMax = 10;
	const float Scene::TimerMax = 40.0f;
	const float Scene::TimerCheck = 0.1f;

	Scene::Scene() :
		m_ground(nullptr),
		m_camera(nullptr),
		m_beeTimer( 0.0f ),
		m_waspTimer( 15.0f ),
		m_beeTimerReset( 5.0f ),
		m_waspTimerReset( 15.0f ),
		m_spawnAmount ( 2 )
	{
		m_ground = new Ground();
		m_camera = new Camera();
	}

	Scene::~Scene()
	{
		delete m_ground;
		delete m_camera;
	}

	void Scene::AdjustSpawnAmount(int adjustedBeeNum)
	{
		m_spawnAmount = adjustedBeeNum;
		
		// Correct BeeNum if it goes too low or too high.
		if (m_spawnAmount <= 0)
		{
			m_spawnAmount = 1;
		}
		else if (m_spawnAmount > SpawnMax)
		{
			m_spawnAmount = 10;
		}
	}

	void Scene::AdjustBeeTimer(float adjustedBeeTimer)
	{
		m_beeTimerReset = adjustedBeeTimer;

		if (m_beeTimerReset <= 0)
		{
			m_beeTimerReset = 1.0f;
		}
		else if (m_beeTimerReset > TimerMax)
		{
			m_beeTimerReset = 40.0f;
		}
	}

	void Scene::Initialise()
	{
		//Create Flower List.
		for (UINT gridX = 0; gridX < FlowerGridSize; ++gridX)
		{
			for (UINT gridZ = 0; gridZ < FlowerGridSize; ++gridZ)
			{
				Flower* flower = new Flower(gridX, gridZ);
				m_flowerList.push_back(flower);
			}
		}

		m_ground->Initialise();
		m_camera->Initialise();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Initialise();
			++itor;
		}
	}

	void Scene::Shutdown()
	{
		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flowerToDelete = *itor;
			delete flowerToDelete;
			++itor;
		}
		m_flowerList.clear();

		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* beeToDelete = *itorBee;
			delete beeToDelete;
			++itorBee;
		}
		m_beeList.clear();

		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* waspToDelete = *itorWasp;
			delete waspToDelete;
			++itorWasp;
		}
		m_waspList.clear();

		m_ground->Shutdown();
	}

	void Scene::Update()
	{
		const float timeStep = utils::Timers::GetFrameTime();

		m_ground->Update();
		m_camera->Update();

		// Update all flowers
		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Update();
			++itor;
		}
		
		containers::List<Bee*>::iterator beeToDeleteItor = nullptr;
		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* bee = *itorBee;
			bee->Update();

			if (bee->OutOfBounds())
			{
				beeToDeleteItor = itorBee;
			}
			++itorBee;
		}

		if (beeToDeleteItor != nullptr)
		{
			Bee* beeToDel = *beeToDeleteItor;
			beeToDel->Shutdown();
			delete beeToDel;

			m_beeList.erase(beeToDeleteItor);
		}

		containers::List<Wasp*>::iterator waspToDeleteItor = nullptr;
		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			wasp->Update();

			if (wasp->OutOfBounds())
			{
				waspToDeleteItor = itorWasp;
			}
			++itorWasp;
		}

		if (waspToDeleteItor != nullptr)
		{
			Wasp* waspToDel = *waspToDeleteItor;
			waspToDel->Shutdown();
			delete waspToDel;

			m_waspList.erase(waspToDeleteItor);
		}

		m_beeTimer -= timeStep;
		if (m_beeTimer < TimerCheck)
		{
			for (UINT i = 0; i < m_spawnAmount; ++i)
			{
				// Spawn a new bee
				Bee* bee = new Bee();
				bee->Initialise();
				m_beeList.push_back(bee);
			}
			m_beeTimer = m_beeTimerReset;
		}

		m_waspTimer -= timeStep;
		if (m_waspTimer < TimerCheck)
		{
			// Spawn a new wasp.
			Wasp* wasp = new Wasp();
			wasp->Initialise();
			m_waspList.push_back(wasp);
			m_waspTimer = m_waspTimerReset;
		}
	}

	Flower* Scene::GetRandFlower()
	{
		int randFlowerObjFromList = (utils::Rand() % (FlowerGridSize*FlowerGridSize));
		int i = 0;

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			if(i == randFlowerObjFromList)
			{	
				Flower* flower = *itor;
				return flower;
			}
			++i;
			++itor;
		}
		return nullptr;
	}
	
	Wasp* Scene::GetWaspClosestToEntity(const Entity* const entity)
	{
		Wasp* closestWasp = nullptr;
		float closestDistance = FLT_MAX;

		XMVECTOR entityPosition = entity->GetPosition();

		containers::List< Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* const wasp = *itorWasp;

			// Get the distance from the passed entity to the wasp
			XMVECTOR waspPosition = wasp->GetPosition();

			XMVECTOR distanceAsVector = entityPosition - waspPosition;

			XMVECTOR distanceAsFloat = XMVector3Length( distanceAsVector );

			// Test to see if this wasp is closer than any others checked so far
			if (*distanceAsFloat.m128_f32 < closestDistance)
			{
				// Store the closest wasp
				closestDistance = *distanceAsFloat.m128_f32;
				closestWasp = wasp;
			}
			++itorWasp;
		}

		return closestWasp;
	}

	Bee* Scene::GetBeeClosestToFlower( const Flower* const flower )
	{
		Bee* closestBee = nullptr;
		float closestDistance = FLT_MAX;
		XMVECTOR flowerPosition = flower->GetPosition();

		containers::List< Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* const bee = *itorBee;

			// Get the distance from the passed entity to the wasp
			XMVECTOR beePosition = bee->GetPosition();

			XMVECTOR distanceAsVector = beePosition - flowerPosition;

			XMVECTOR distanceAsFloat = XMVector3Length(distanceAsVector);

			// Test to see if this wasp is closer than any others checked so far
			if (*distanceAsFloat.m128_f32 < closestDistance )
			{
					// Store the closest wasp
					closestDistance = *distanceAsFloat.m128_f32;
					closestBee = bee;
			}
			++itorBee;
		}
		return closestBee;
	}

	Flower* Scene::GetHighestNectarFlower()
	{
		Flower* highestNectarFlower = nullptr;
		float highestNectar = 0.0f;

		containers::List< Flower*>::iterator itorFlower = m_flowerList.begin();
		while (itorFlower != m_flowerList.end())
		{
			Flower* const flower = *itorFlower;

			// Get the nectar level
			XMVECTOR flowerPosition = flower->GetPosition();
			float flowerNectarNum = flower->GetNectarFloat();
			
			// Check if nectar value is higher than last.
			if (flowerNectarNum > highestNectar)
			{
				// Store the highest nectar flower.
				highestNectar = flowerNectarNum;
				highestNectarFlower = flower;
			}
			++itorFlower;
		}
		return highestNectarFlower;
	}

	void Scene::Render()
	{
		m_ground->Render();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Render();
			++itor;
		}

		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* bee = *itorBee;
			bee->Render();
			++itorBee;
		}

		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			wasp->Render();
			++itorWasp;
		}
	}
} // namespace scene