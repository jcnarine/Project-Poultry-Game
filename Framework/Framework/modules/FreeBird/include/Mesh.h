//Mesh class to load our objects
/*
	Tyler Wong
	2020-10-24
*/

#pragma once
#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "VertexArrayObject.h"

namespace freebird
{
	class Mesh
	{
	public:
		Mesh(const std::string& fileName, const glm::vec3& inColor = glm::vec3(1.0f));
		Mesh();
		VertexArrayObject::sptr makeVAO();
		VertexArrayObject::sptr vao;
		void Render();
		
	protected:
		std::vector<float> interleaved;
		std::vector<unsigned int> vertIndices, uvIndices, normIndices; 
		static const std::vector<BufferAttribute> buffAttibs; 
	};
}