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

	float	yRotAdjustment = 0.0f;
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
}