#include "GameProgExercise01.h"
#include "Scene\Scene.h"
#include "Scene\Ground.h"

Scene::Scene():
	m_ground( nullptr )	
{
}


void Scene::Initialise()
{
	m_ground = new Ground();
	m_ground->SetupTriangle();
	
	
}

void Scene::Shutdown()
{
	if (m_ground)
	{
		delete m_ground;
		m_ground = nullptr;
	}
}

void Scene::Update()
{
	//m_ground->Update();
}

void Scene::Render()
{
	m_ground->Render();
}