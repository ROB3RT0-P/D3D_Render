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
		//m_testObject1( nullptr ),
		//m_testObject2( nullptr ),
		m_ground( nullptr ),
		m_camera( nullptr )
		//m_bee( nullptr ),
		//m_wasp( nullptr )
	{
		//m_testObject1 = new TestObject();
		//m_testObject2 = new TestObject();
		m_ground = new Ground();
		m_camera = new Camera();
		//m_bee = new Bee();
		//m_wasp = new Wasp();
	}

	Scene::~Scene()
	{
		//delete m_testObject1;
		//delete m_testObject2;
		delete m_ground;
		delete m_camera;
		//delete m_bee;
		//delete m_wasp;
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

		//Create Bee list.
		for (UINT beeGridZ = 0; beeGridZ < BeeNum; ++beeGridZ)
		{
			Bee* bee = new Bee();
			m_beeList.push_back(bee);
		}

		//Create Wasp list.
		for (UINT waspGridZ = 0; waspGridZ < WaspNum/10; ++waspGridZ)
		{
			Wasp* wasp = new Wasp();
			m_waspList.push_back(wasp);
		}

		// 1st test object
		//m_testObject1->Initialise();
		m_ground->Initialise();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Initialise();
			++itor;
		}

		containers::List<Bee*>::iterator itorBee = m_beeList.begin();
		while (itorBee != m_beeList.end())
		{
			Bee* bee = *itorBee;
			bee->Initialise();
			++itorBee;
		}

		containers::List<Wasp*>::iterator itorWasp = m_waspList.begin();
		while (itorWasp != m_waspList.end())
		{
			Wasp* wasp = *itorWasp;
			wasp->Initialise();
			++itorBee;
		}

		/*
		position = XMVectorSet( -2.0f, 0.0f, 0.0f, 1.0f );
		m_testObject1->SetPosition( position );

		// 2nd test object
		m_testObject2->Initialise();

		position = XMVectorSet( 2.0f, 0.0f, 0.0f, 1.0f );
		m_testObject2->SetPosition( position );
		orientation = XMMatrixRotationY( XM_PIDIV2 );
		m_testObject2->SetOrientation( orientation );
		*/

		m_camera->Initialise();

		m_bee->Initialise();

		m_wasp->Initialise();
	}

	void Scene::Shutdown()
	{
		/*int testInt = 7;
		int* testIntPtr = &testInt;
		int intBackAgain = *testIntPtr;*/

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

		//m_testObject2->Shutdown();
		//m_testObject1->Shutdown();
		m_ground->Shutdown();
		//m_bee->Shutdown();
		//m_wasp->Shutdown();
	}

	void Scene::Update()
	{
		//m_testObject1->Update();
		//m_testObject2->Update();
		m_ground->Update();
		m_camera->Update();
		//m_bee->Update();
		//m_wasp->Update();

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

		if (m_bee->OutOfBounds())
		{
			m_bee->Shutdown();
			delete m_bee;

			m_bee = new Bee();
			m_bee->Initialise();
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

		if (m_wasp->OutOfBounds())
		{
			m_wasp->Shutdown();
			delete m_wasp;

			m_wasp = new Wasp();
			m_wasp->Initialise();
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

	void Scene::Render()
	{
		//m_testObject1->Render();
		//m_testObject2->Render();
		m_ground->Render();
		m_bee->Render();
		m_wasp->Render();

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