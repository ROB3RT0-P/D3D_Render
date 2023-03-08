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
	Scene::Scene() :
		m_ground( nullptr ),
		m_camera( nullptr )
	{
		m_ground = new Ground();
		m_camera = new Camera();
	}

	Scene::~Scene()
	{
		delete m_ground;
		delete m_camera;
	}

	void Scene::Initialise()
	{
		m_camera->Initialise();
		m_beeTimer = 5.0f;
		m_waspTimer = 15.0f;

		//Create Flower List.
		for (UINT gridX = 0; gridX < FlowerGridSize; ++gridX)
		{
			for (UINT gridZ = 0; gridZ < FlowerGridSize; ++gridZ)
			{
				Flower* flower = new Flower(gridX, gridZ);
				m_flowerList.push_back(flower);
			}
		}
	
		//Create Wasp list.
		for (UINT waspGridZ = 0; waspGridZ < WaspNum; ++waspGridZ)
		{
			Wasp* wasp = new Wasp();
			m_waspList.push_back(wasp);
		}


		m_ground->Initialise();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Initialise();
			++itor;
		}

		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			wasp->Initialise();
			++itorWasp;
		}

		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* bee = *itorBee;
			bee->Initialise();
			++itorBee;
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
		float timeStep = utils::Timers::GetFrameTime();
		
		m_beeTimer -= timeStep;
		m_waspTimer -= timeStep;

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

		bool needNewWasp = false;
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

		if (m_beeTimer < 0.1f)
		{
			// Spawn a new bee
			Bee* bee = new Bee();
			bee->Initialise();
			m_beeList.push_back(bee);
			m_beeTimer = 5.0f;
		}

		if (m_waspTimer < 0.1f)
		{
			Wasp* wasp = new Wasp();
			wasp->Initialise();
			m_waspList.push_back(wasp);
			m_waspTimer = 15.0f;
		}
	}

	Flower* Scene::GetRandFlower()
	{
		int randFlowerFromList = (utils::Rand() % (FlowerGridSize*FlowerGridSize));
		int i = 0;

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			if(i == randFlowerFromList)
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

		XMVECTOR entityPostion = entity->GetPosition();

		containers::List< Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* const wasp = *itorWasp;

			// Get the distance from the passed entity to the wasp
			XMVECTOR waspPosition = wasp->GetPosition();

			XMVECTOR distanceAsVector = entityPostion - waspPosition;

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