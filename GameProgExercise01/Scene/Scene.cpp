#include "GameProgExercise01.h"
#include "DX\DeviceResources.h"
#include "Core.h"
#include "Utils\File.h"
#include "Scene\Scene.h"
#include "Scene\Entities\TestObject.h"
#include "Scene\Entities\Ground.h"
#include "Scene\Camera.h"

using namespace DirectX;

namespace scene
{

Scene::Scene() :
	m_testObject1( nullptr ),
	m_testObject2( nullptr ),
	m_ground( nullptr ),
	m_camera( nullptr )
{
	m_testObject1 = new TestObject();
	m_testObject2 = new TestObject();
	m_ground = new Ground();
	m_camera = new Camera();
}

Scene::~Scene()
{
	delete m_testObject1;
	delete m_testObject2;
	delete m_ground;
	delete m_camera;
}

void Scene::Initialise()
{
	XMVECTOR position;
	XMMATRIX orientation;

	// 1st test object
	m_testObject1->Initialise();
	m_ground->Initialise();

	position = XMVectorSet( -2.0f, 0.0f, 0.0f, 1.0f );
	m_testObject1->SetPosition( position );

	// 2nd test object
	m_testObject2->Initialise();

	position = XMVectorSet( 2.0f, 0.0f, 0.0f, 1.0f );
	m_testObject2->SetPosition( position );
	orientation = XMMatrixRotationY( XM_PIDIV2 );
	m_testObject2->SetOrientation( orientation );

	m_camera->Initialise();
}

void Scene::Shutdown()
{
	m_testObject2->Shutdown();
	m_testObject1->Shutdown();
	m_ground->Shutdown();
}

void Scene::Update()
{
	m_testObject1->Update();
	m_testObject2->Update();
	m_ground->Update();
	m_camera->Update();
}

void Scene::Render()
{
	m_testObject1->Render();
	m_testObject2->Render();
	m_ground->Render();
}

} // namespace scene