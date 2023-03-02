#pragma once

#include "Scene\Entity.h"

namespace scene
{

class TestObject : public Entity
{
	public:
		TestObject();

		void				Initialise();
		void				Render();

	private:
		static const UINT NumVertices = 9;
};
} // namespace scene
