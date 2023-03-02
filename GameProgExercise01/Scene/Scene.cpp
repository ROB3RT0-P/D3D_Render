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

using namespace DirectX;

namespace scene
{

	Scene::Scene() :
		m_testObject1( nullptr ),
		m_testObject2( nullptr ),
		m_ground( nullptr ),
		m_camera( nullptr ),
		m_bee( nullptr )
	{
		m_testObject1 = new TestObject();
		m_testObject2 = new TestObject();
		m_ground = new Ground();
		m_camera = new Camera();
		m_bee = new Bee();
	}

	Scene::~Scene()
	{
		delete m_testObject1;
		delete m_testObject2;
		delete m_ground;
		delete m_camera;
		delete m_bee;
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

		XMVECTOR position;
		XMMATRIX orientation;

		// 1st test object
		m_testObject1->Initialise();
		m_ground->Initialise();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Initialise();
			++itor;
		}

		position = XMVectorSet( -2.0f, 0.0f, 0.0f, 1.0f );
		m_testObject1->SetPosition( position );

		// 2nd test object
		m_testObject2->Initialise();

		position = XMVectorSet( 2.0f, 0.0f, 0.0f, 1.0f );
		m_testObject2->SetPosition( position );
		orientation = XMMatrixRotationY( XM_PIDIV2 );
		m_testObject2->SetOrientation( orientation );

		m_camera->Initialise();

		m_bee->Initialise();
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

		m_testObject2->Shutdown();
		m_testObject1->Shutdown();
		m_ground->Shutdown();
		m_bee->Shutdown();
	}

	void Scene::Update()
	{
		m_testObject1->Update();
		m_testObject2->Update();
		m_ground->Update();
		m_camera->Update();
		m_bee->Update();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Update();
			++itor;
		}

		if (m_bee->OutOfBounds())
		{
			m_bee->Shutdown();
			delete m_bee;

			m_bee = new Bee();
			m_bee->Initialise();
		}
	}

	Flower* Scene::GetFlower()
	{
		Flower* flower = *m_flowerList.begin();
		return flower;
	}

	void Scene::Render()
	{
		//m_testObject1->Render();
		//m_testObject2->Render();
		m_ground->Render();
		m_bee->Render();

		containers::List< Flower*>::iterator itor = m_flowerList.begin();
		while (itor != m_flowerList.end())
		{
			Flower* flower = *itor;
			flower->Render();
			++itor;
		}
	}
} // namespace scene