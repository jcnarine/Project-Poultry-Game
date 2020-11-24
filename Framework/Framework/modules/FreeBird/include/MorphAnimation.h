#pragma once

#include "Entity.h"
#include <Mesh.h>

namespace freebird
{

	class MorphAnimation
	{
	public:
		MorphAnimation(Entity& ent);

		void Update(float deltaTime);

		void SetFrames(const std::vector<std::unique_ptr<Mesh>>& frames);
		void SetTime(float time);

	private:

		class MorphData
		{
		public:

			std::vector<const Mesh*> frames;
			float frameTime;

			MorphData();
		};

		std::unique_ptr<MorphData> data;

		float timer;
		size_t frame;
		Entity* thisEnt;
	};






}