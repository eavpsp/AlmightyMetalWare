#include "GameModel.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "../debug/debug.h"
std::string get_file_contents(const char* filename)
{
    debugLog("GameModel.cpp: Loading %s", filename);
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        debugLog("GameModel.cpp: Failed to open %c", filename);
        return "";
    }

    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    in.seekg(0, std::ios::beg);

    std::string contents(size, '\0');
    in.read(&contents[0], size);
    in.close();
    debugLog("GameModel.cpp: Get File Contents Read Complete");

    return contents;
}

GameModel::GameModel(const char* FILENAME)
{
	meshes = std::vector<MeshData>();
	translationsMeshes = std::vector<glm::vec3>();
	rotationsMeshes = std::vector<glm::quat>();
	scalesMeshes = std::vector<glm::vec3>();
	matricesMeshes = std::vector<glm::mat4>();
	debugLog("Loading %s", FILENAME);
	// Make a JSON object
	std::string text = get_file_contents(FILENAME);
	debugLog("Text Loaded");	
	JSON = json::parse(text);
	debugLog("Json Parsed");	

	// Get the binary data
	GameModel::file = file;
	data = getData();

	// Traverse all nodes
	traverseNode(0);
	debugLog("Loaded %s", FILENAME);
	
}

GameModel::GameModel(std::vector<MeshData> meshes)
{
    this->meshes = meshes;
   
}

void GameModel::loadMesh(unsigned int indMesh)
{
	debugLog("Loading Mesh %d", indMesh);
	if(JSON["meshes"][indMesh] == nullptr)
	{
		debugLog("Error: Mesh %d does not exist", indMesh);
		return;
	}
	// Get all accessor indices
	unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];
	debugLog("Got Accessors");
	// Use accessor indices to get all vertices components
	std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
	std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
	std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
	std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
	std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
	std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);
	if(texVec.size() == 0)
	{
		debugLog("No Texture Coords Found");
	}
	if(normalVec.size() == 0)
	{
		debugLog("No Normals Found");
	}
	if(positions.size() == 0)
	{
		debugLog("No Vertices Found");
	}
	debugLog("Got Vertices");
	// Combine all the vertex components and also get the indices and textures
	std::vector<VertexLit> vertices = assembleVertices(positions, normals, texUVs);
	std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
	//std::vector<MW_Texture> textures = getTextures();
	std::vector<MW_Texture> textures;
	debugLog("Got Mesh %d", indMesh);
	// Combine the vertices, indices, and textures into a mesh
	MeshData *mesh = new MeshData();
	mesh->initMeshLitTexture(vertices, indices, textures);
	meshes.push_back(*mesh);
	debugLog("Mesh %d Loaded", indMesh);
}

void GameModel::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{
	// Current node
	json node = JSON["nodes"][nextNode];
	if(node == NULL)
	{
		debugLog("Node: %s does not exist", node["name"].get<std::string>().c_str());
		return;
	}
	debugLog("Current Node: %s", node["name"].get<std::string>().c_str());
	// Get translation if it exists
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = glm::make_vec3(transValues);
	}
	else{
		debugLog("Node: %s has no translation", node["name"].get<std::string>().c_str());
	}
	// Get quaternion if it exists
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotValues[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotation = glm::make_quat(rotValues);
	}
	else{
		debugLog("Node: %s has no rotation", node["name"].get<std::string>().c_str());
	}
	// Get scale if it exists
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
			scaleValues[i] = (node["scale"][i]);
		scale = glm::make_vec3(scaleValues);
	}//
	else{
		debugLog("Node: %s has no scale", node["name"].get<std::string>().c_str());
	}
	// Get matrix if it exists
	glm::mat4 matNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
			matValues[i] = (node["matrix"][i]);
		matNode = glm::make_mat4(matValues);
	}
	else
	{
		debugLog("Node: %s has no matrix", node["name"].get<std::string>().c_str());
	}

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Use translation, rotation, and scale to change the initialized matrices
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Multiply all matrices together
	glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

	// Check if the node contains a mesh and if it does load it
	if (node.find("mesh") != node.end())
	{
		debugLog("Node: %s has mesh", node["name"].get<std::string>().c_str());
		translationsMeshes.push_back(translation);
		rotationsMeshes.push_back(rotation);
		scalesMeshes.push_back(scale);
		matricesMeshes.push_back(matNextNode);

		loadMesh(node["mesh"]);
	}
	else
		debugLog("Node: %s has no mesh", node["name"].get<std::string>().c_str());

	// Check if the node has children, and if it does, apply this function to them with the matNextNode
	if (node.find("children") != node.end() )
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
			traverseNode(node["children"][i], matNextNode);
	}
	else{
		debugLog("Node: %s has no children", node["name"].get<std::string>().c_str());
	}
	debugLog("Node: %s done", node["name"].get<std::string>().c_str());
}

std::vector<unsigned char> GameModel::getData()
{
	debugLog("Loading Data");
	// Get the uri of the .bin file
	std::string uri = JSON["buffers"][0]["uri"];
	if(uri == "")	
	{
		debugLog("Error: Buffer does not exist");
		return std::vector<unsigned char>();
	}
	// Open the file and get the size of it
	std::string fileStr = std::string(file);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	FILE *file = fopen(("romfs:/" + fileDirectory + uri).c_str(), "rb");
	if(file == nullptr)
	{
		debugLog("Error: File does not exist");
		return std::vector<unsigned char>();
	}
	fseek(file, 0, SEEK_END);
	unsigned int size = ftell(file);
	rewind(file);

	// Store the data in a vector
	std::vector<unsigned char> data(size);
	fread(&data[0], 1, size, file);
	fclose(file);
	debugLog("Data Loaded");
	return data;
}

std::vector<float> GameModel::getFloats(json accessor)
{
	if(accessor == nullptr)
	{
		debugLog("Error: Accessor does not exist");
		return std::vector<float>();
	}
	std::vector<float> floatVec;
	debugLog("Loading floats");
	// Get properties from the accessor
	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	// Get properties from the bufferView
	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];
	if(bufferView == nullptr)
	{	
		debugLog("Error: BufferView %d does not exist", buffViewInd);
		return floatVec;
	}
	// Interpret the type and store it into numPerVert
	unsigned int numPerVert;
	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else (debugLog("Error: %s is not a valid accessor type", type.c_str()));

	// Go over all the bytes in the data at the correct place using the properties from above
	unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * numPerVert;
	for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i)
	{
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floatVec.push_back(value);
	}

	return floatVec;
}

std::vector<GLuint> GameModel::getIndices(json accessor)
{
	std::vector<GLuint> indices;

	// Get properties from the accessor
	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	// Get properties from the bufferView
	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	// Get indices with regards to their type: unsigned int, unsigned short, or short
	unsigned int beginningOfData = byteOffset + accByteOffset;
	if (componentType == 5125)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
		{
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5123)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5122)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}

	return indices;
}
std::vector<MW_Texture> GameModel::getTextures()
{
	debugLog("Loading Textures");
	std::vector<MW_Texture> textures;

	auto texIter = loadedTexName.begin();
	std::string baseDir = "romfs:/";

	for (const auto& image : JSON["images"])
	{
		debugLog("Loading Texture %s", image["uri"]);
		std::string texPath = image["uri"];
		texIter = std::lower_bound(loadedTexName.begin(), loadedTexName.end(), texPath);
		if (texIter != loadedTexName.end() && *texIter == texPath)
		{
			debugLog("Texture %s already loaded", texPath.c_str());
			textures.push_back(loadedTex[texIter - loadedTexName.begin()]);
		}
		else
		{
			if (texPath.find("baseColor") != std::string::npos)
			{
				MW_Texture diffuse((baseDir + texPath).c_str());
				textures.push_back(diffuse);
				loadedTex.push_back(diffuse);
				loadedTexName.push_back(texPath);
				debugLog("Texture %s loaded", texPath.c_str());
			}
			else if (texPath.find("metallicRoughness") != std::string::npos)
			{
				MW_Texture specular((baseDir + texPath).c_str());
				textures.push_back(specular);
				loadedTex.push_back(specular);
				loadedTexName.push_back(texPath);
				debugLog("Texture %s loaded", texPath.c_str());
			}
			else
			{
				debugLog("Texture %s not found", texPath.c_str());
			}
		}
	}

	debugLog("Loaded Textures");
	return textures;
}

std::vector<VertexLit> GameModel::assembleVertices
(
	std::vector<glm::vec3> positions,
	std::vector<glm::vec3> normals,
	std::vector<glm::vec2> texUVs
)
{
	std::vector<VertexLit> vertices;
	for (int i = 0; i < positions.size(); i++)
	{
		vertices.push_back
		(
			VertexLit
			{
				positions[i],
				normals[i],
				texUVs[i],
			}
		);
	}
	debugLog("Assembled Vertices");
	return vertices;
}

std::vector<glm::vec2> GameModel::groupFloatsVec2(std::vector<float> floatVec)
{
	std::vector<glm::vec2> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}
std::vector<glm::vec3> GameModel::groupFloatsVec3(std::vector<float> floatVec)
{
	std::vector<glm::vec3> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}
std::vector<glm::vec4> GameModel::groupFloatsVec4(std::vector<float> floatVec)
{
	std::vector<glm::vec4> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}