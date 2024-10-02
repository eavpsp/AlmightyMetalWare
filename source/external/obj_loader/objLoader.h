#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <VertexBuffer.h>

namespace util 
{
	std::vector<float> load_model_from_file(const char* filename, glm::mat4 preTransform);
	std::vector<VertexLit> load_model_from_file_obj(const char* filename, glm::mat4 preTransform);
};

#endif