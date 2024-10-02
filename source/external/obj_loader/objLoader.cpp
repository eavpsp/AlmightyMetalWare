#include <objLoader.h>
#include <tiny_obj_loader.h>
#include <iostream>
#include "../../debug/debug.h"
std::vector<VertexLit> util::load_model_from_file_obj(const char* filename, glm::mat4 preTransform) 
{
	
	std::vector<VertexLit> vertices;

	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, error;

	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, filename, "romfs:/")) 
	{
   	 	debugLog("Error: %s", error.c_str());
	}
	for (const auto& shape : shapes) 
	{
		for (const auto& index : shape.mesh.indices) 
		{

			VertexLit vert = 
			{
				glm::vec3(attributes.vertices[3 * index.vertex_index],attributes.vertices[3 * index.vertex_index + 1],attributes.vertices[3 * index.vertex_index + 2]),
				glm::vec3(attributes.normals[3 * index.normal_index],attributes.normals[3 * index.normal_index + 1],attributes.normals[3 * index.normal_index + 2]),
				glm::vec2(attributes.texcoords[2 * index.texcoord_index],attributes.texcoords[2 * index.texcoord_index + 1])
			};
			debugLog("Vertex: %f %f %f", vert.position.x, vert.position.y, vert.position.z);
			debugLog("Normal: %f %f %f", vert.normal.x, vert.normal.y, vert.normal.z);
			debugLog("TexCoord: %f %f", vert.texUV.x, vert.texUV.y);
			vertices.push_back(vert);
		}



		
	}
	debugLog("OBJ Model Loaded----------");
	debugLog("Vertices: %d", vertices.size());
	debugLog("Shapes: %d", shapes.size());
	debugLog("Materials: %d", materials.size());
	debugLog("--------------------------");

	return vertices;
}
/**
 * Loads a model from a file and returns a vector of floats containing the vertices,
 * where each vertex is represented by 8 floats: 3 floats for the position, 2 floats
 * for the texture coordinates, and 3 floats for the normal. The vertices are
 * transformed by the given preTransform matrix before being returned.
 *
 * @param filename The path to the file containing the model.
 * @param preTransform A transformation matrix to apply to the vertices before
 *                     returning them.
 * @return A vector of floats containing the vertices of the model.
 */
std::vector<float> util::load_model_from_file(const char* filename, glm::mat4 preTransform) {
	
	std::vector<float> vertices;

	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, error;

	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, filename, "romfs:/")) {
   	 debugLog("Error: %s", error.c_str());
	}
	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {

			glm::vec4 pos = {
				attributes.vertices[3 * index.vertex_index],
				attributes.vertices[3 * index.vertex_index + 1],
				attributes.vertices[3 * index.vertex_index + 2],
				1
			};

			pos = preTransform * pos;

			glm::vec3 normal = {
				attributes.normals[3 * index.normal_index],
				attributes.normals[3 * index.normal_index + 1],
				attributes.normals[3 * index.normal_index + 2]
			};

			normal = glm::normalize(glm::mat3(preTransform) * normal);

			glm::vec2 texCoord = {
				attributes.texcoords[2 * index.texcoord_index],
				attributes.texcoords[2 * index.texcoord_index + 1],
			};

			debugLog("Vertex: %f %f %f", pos.x, pos.y, pos.z);
			debugLog("Normal: %f %f %f", normal.x, normal.y, normal.z);
			debugLog("TexCoord: %f %f", texCoord.x, texCoord.y);
			vertices.push_back(pos.x);
			vertices.push_back(pos.y);
			vertices.push_back(pos.z);
			vertices.push_back(texCoord.x);
			vertices.push_back(texCoord.y);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
		}
	}
	debugLog("OBJ Model Loaded----------");
	debugLog("Vertices: %d", vertices.size() / 8);
	debugLog("Shapes: %d", shapes.size());
	debugLog("Materials: %d", materials.size());
	debugLog("--------------------------");

	return vertices;
}