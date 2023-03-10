#include "GameProgExercise01.h"
#include "Core.h"
#include "Input.h"
#include "Scene\Camera.h"
#include "Scene\Scene.h"

void Input::Initialise()
{
	m_keyboard = new DirectX::Keyboard();
}

void Input::Shutdown()
{
	delete m_keyboard;
}

void Input::Update()
{
	const Core* const core = Core::Get();
	scene::Scene* scene = core->GetScene();
	scene::Camera* const camera = scene->GetCamera();

	float yRotAdjustment = 0.0f;
	auto kb = m_keyboard->GetState();
	if (kb.Right)
	{
		yRotAdjustment = -1.0f;
	}
	else if (kb.Left)
	{
		yRotAdjustment = 1.0f;
	}
	camera->AdjustYRotation(yRotAdjustment);

	float xRotAdjustment = 0.0f;
	if (kb.Up)
	{
		xRotAdjustment = -1.0f;
	}
	else if (kb.Down)
	{
		xRotAdjustment = 1.0f;
	}
	camera->AdjustXRotation(xRotAdjustment);

	float height = 0.0f;
	if (kb.I)
	{
		height = 1.0f;
	}
	else if (kb.K)
	{
		height = -1.0f;
	}
	camera->AdjustHeight(height);

	int numberOfBees = scene->GetSpawnAmount();
	if (kb.A)
	{
			numberOfBees += 1;
	}
	else if(kb.D)
	{
			numberOfBees -= 1;
	}
	scene->AdjustSpawnAmount( numberOfBees ); // TODO rename

	float beeTimer = scene->GetBeeTimer();
	if (kb.W)
	{
		beeTimer += 1;
	}
	else if (kb.S)
	{
		beeTimer -= 1;
	}
	scene->AdjustBeeTimer(beeTimer);


}