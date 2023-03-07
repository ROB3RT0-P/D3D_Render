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

		//Create Bee list.
		for (UINT beeGridZ = 0; beeGridZ < BeeNum; ++beeGridZ)
		{
			Bee* bee = new Bee();
			m_beeList.push_back(bee);
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
		m_ground->Update();
		m_camera->Update();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Update();
			++itor;
		}

		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* bee = *itorBee;
			bee->Update();
			++itorBee;

			if (bee->OutOfBounds())
			{
				bee->Shutdown();
				delete bee;
				
				bee = new Bee();
				bee->Initialise();
			}
		}

		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			wasp->Update();
			++itorWasp;

			if (wasp->OutOfBounds())
			{
				wasp->Shutdown();
				delete wasp;

				wasp = new Wasp();
				wasp->Initialise();
			}
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

	Wasp* Scene::GetWasps()
	{
		containers::List< Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			return wasp;
			++itorWasp;
		}
		return nullptr;
	}

	/*
	Wasp* Scene::GetWaspClosestToEntity(const Entity* const entity)
	{
		Wasp* wasp = ;
		return wasp;
	}
	*/

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