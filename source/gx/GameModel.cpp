#include "GameModel.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "../debug/debug.h"
#include <ResourceManager.h>

//MAKE CHILDREN MESHES
extern ResourceManager *gameResourceManager;
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

/**
 * @brief Generates a vertex buffer containing all the vertices and indices of this model, and stores it in the vertexBuffer field.
 * 
 * This function combines all the vertices and indices of the meshes in this model, and stores them in a single vertex buffer. This vertex buffer is then added to the vertexArray field.
 * 
 * This function is called by the ResourceManager when a model is loaded.
 */
void GameModel::GenereteVertexBuffer()
{
	vertexArray->Bind();
	std::vector<VertexLit> vertices;
	std::vector<GLuint> indices;
	for (int i = 0; i < meshes.size(); i++)
	{
		vertices.insert(vertices.end(), meshes[i].vertices.begin(), meshes[i].vertices.end());
		indices.insert(indices.end(), meshes[i].indices.begin(), meshes[i].indices.end());
	}
	vertexBuffer = new VertexBuffer();
	vertexBuffer->initVertexBuffer(&vertices[0], vertices.size() * sizeof(VertexLit), LIT, vertices.size());
	vertexBuffer->ib = new IndexBuffer(indices.size());
	vertexBuffer->ib->Bind(indices.data());
	VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    vertexArray->AddBuffer(*vertexBuffer,layout);
	vertexBuffer->UnBind();
    vertexArray->UnBind();
    vertexBuffer->ib->UnBind();
	debugLog("GameModel.cpp: Vertex Buffer Generated");
}

GameModel::GameModel(const char *FILENAME) // add custom shader types
{
	vertexArray = new VertexArray(); //create VAO for binding and drawing
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
	int nodeSize = 0;
	 if (JSON.find("scenes") != JSON.end()) {
        const auto& scenes = JSON["scenes"];
        if (scenes.size() > 0) {
            nodeSize = scenes[0]["nodes"].size();
        }
    }
	debugLog("Node Size: %d", nodeSize);
	// Get the binary data
	GameModel::file = file;
	data = getData();

	// Traverse all nodes
	for (int i = 0; i < nodeSize; i++)
	{
		traverseNode(i);

		/* code */
	}
	//get all data loaded and create VAo VBO and EBO
	
	debugLog("Loaded %s", FILENAME);
	GenereteVertexBuffer();
}


GameModel::GameModel(std::vector<MeshData> meshes, ShaderType shaderType)
{
	//set VAO ID
	switch (shaderType)
	{
	case ShaderType::UNLIT:
		vertexArray = new VertexArray();
		break;
	case ShaderType::LIT:
		vertexArray = new VertexArray();
		break;
	default://TEX_UNLIT	
		vertexArray = new VertexArray();
		break;
	}
    this->meshes = meshes;
	for (int i = 0; i < meshes.size(); i++)
	{
	
		MeshData *mesh = new MeshData(meshes[i].vertices, meshes[i].indices, meshes[i].textures);
		
		meshes.push_back(*mesh);


	}
	GenereteVertexBuffer();


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
	std::vector<MW_Texture> textures = getTextures();
	debugLog("Got Mesh %d", indMesh);
	// Combine the vertices, indices, and textures into a mesh
	//Binds VBO and EBO to VAO
	
	MeshData *mesh = new MeshData(vertices, indices, textures);
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
	int count = 0;
	for (const auto& image : JSON["images"])
	{
		debugLog("Loading Texture %s", image["uri"]);
		std::string imagePath = image["uri"];
		std::string texPath = baseDir + imagePath;
		texIter = std::lower_bound(loadedTexName.begin(), loadedTexName.end(), texPath);
		if (texIter != loadedTexName.end() && *texIter == texPath)
		{
			debugLog("Texture %s already loaded", texPath.c_str());
			textures.push_back(loadedTex[texIter - loadedTexName.begin()]);
		}
		else
		{
			if (access(texPath.c_str(), F_OK) != -1)
			{
				MW_Texture diffuse((texPath).c_str());
				textures.push_back(diffuse);
				loadedTex.push_back(diffuse);
				loadedTexName.push_back(texPath);
				debugLog("Texture %s loaded", texPath.c_str());
			}
			else
			{
				debugLog("Texture %s not found", texPath.c_str());
			}
		}
		count++;
	}

	debugLog("Loaded Textures: %d", count);	
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

//TINY GLTF--------------------------------------------------------------------------------

GLTFStaticMesh::GLTFStaticMesh(const char* filename, float scale) {

    tinygltf::TinyGLTF loader;
    std::string error;
    std::string warning;

    loader.LoadASCIIFromFile(&model, &error, &warning, filename);
    if (!warning.empty()) {
       debugLog("GLTFStaticMesh: %s", warning.c_str());
    }
	else{
		debugLog("GLTFStaticMesh: Loaded %s", filename);
	}
    if (!error.empty()) {
       debugLog("GLTFStaticMesh: %s", error.c_str());
    }
    VAO_and_EBOs = bindModel();
    this->scale = scale;
}

/*
* Create ebos for the given mesh and register them in the set.
*/
void GLTFStaticMesh::bindMesh(std::map<int, GLuint>& ebos, tinygltf::Mesh& mesh) {

    for (int i = 0; i < model.bufferViews.size(); ++i) {
        const tinygltf::BufferView& bufferView = model.bufferViews[i];
        if (bufferView.target == 0) {
            debugLog("GLTFStaticMesh: Unsupported bufferView %d", i);
            continue;  // Unsupported bufferView.
                       /*
                         From spec2.0 readme:
                         https://github.com/KhronosGroup/glTF/tree/master/specification/2.0
                                  ... drawArrays function should be used with a count equal to
                         the count            property of any of the accessors referenced by the
                         attributes            property            (they are all equal for a given
                         primitive).
                       */
        }

        const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
	
        GLuint ebo;
        glGenBuffers(1, &ebo);
        ebos[i] = ebo;
        glBindBuffer(bufferView.target, ebo);

        glBufferData(bufferView.target, bufferView.byteLength,
            &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
    }

    for (int i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];
        tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

        for (auto& attrib : primitive.attributes) {
            tinygltf::Accessor accessor = model.accessors[attrib.second];
            int byteStride =
                accessor.ByteStride(model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, ebos[accessor.bufferView]);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int vaa = -1;
            if (attrib.first.compare("POSITION") == 0) vaa = 0;
            if (attrib.first.compare("NORMAL") == 0) vaa = 2;
            if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 1;
            if (vaa > -1) {
                glEnableVertexAttribArray(vaa);
                glVertexAttribPointer(vaa, size, accessor.componentType,
                    accessor.normalized ? GL_TRUE : GL_FALSE,
                    byteStride, ((char*)NULL + accessor.byteOffset));
            }
            else
                debugLog("GLTFStaticMesh: Unsupported attribute %s", attrib.first.c_str());
        }
	

    }

}


/*
* Inspect a node, create an ebo for its mesh if it has one,
* and recursively check its children
*/
void GLTFStaticMesh::bindModelNodes(std::map<int, GLuint>& ebos, tinygltf::Node& node) {

    if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
        //this node holds a mesh, bind it
        bindMesh(ebos, model.meshes[node.mesh]);
    }

    //recursively bind children
    for (int i = 0; i < node.children.size(); i++) {
        assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
        bindModelNodes(ebos, model.nodes[node.children[i]]);
    }
}

/*
* Parse the loaded model data,
* create a vertex array object
* and a set of element buffer objects (Scene might have multiple objects).
*/
std::pair<GLuint, std::map<int, GLuint>> GLTFStaticMesh::bindModel() {
    std::map<int, GLuint> ebos;
	vertexArray = new VertexArray();
	vertexArray->Bind();

    //create an ebo for each node in the scene
    const tinygltf::Scene& scene = model.scenes[model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
        assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
        bindModelNodes(ebos, model.nodes[scene.nodes[i]]);
    }

   vertexArray->UnBind();
    //cleanup: make sure only ebos are stored
    for (auto it = ebos.cbegin(); it != ebos.cend();) {
        tinygltf::BufferView bufferView = model.bufferViews[it->first];
        if (bufferView.target != GL_ELEMENT_ARRAY_BUFFER) {
            glDeleteBuffers(1, &ebos[it->first]);
            ebos.erase(it++);
        }
        else {
            ++it;
        }
    }
    return { gameResourceManager->s_vao_3D, ebos };
}

/*
* draw each of the primitives in the given mesh
*/
void GLTFStaticMesh::drawMesh(const std::map<int, GLuint>& ebos, tinygltf::Mesh& mesh) {
    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];
        tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];;
		vertexArray->Bind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(indexAccessor.bufferView));

        glDrawElements(primitive.mode, indexAccessor.count,
            indexAccessor.componentType,
            ((char*)NULL + indexAccessor.byteOffset));
		vertexArray->UnBind();
    }
}

/*
* Inspect a given node, draw any meshes it has, and
* recursively inspect its children
*/
void GLTFStaticMesh::drawModelNodes(tinygltf::Node& node) {
    if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
        drawMesh(VAO_and_EBOs.second, model.meshes[node.mesh]);
    }
    for (size_t i = 0; i < node.children.size(); i++) {
        drawModelNodes(model.nodes[node.children[i]]);
    }
}

/*
* High-level method for drawing the model
*/
void GLTFStaticMesh::draw() {

    const tinygltf::Scene& scene = model.scenes[model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
        drawModelNodes(model.nodes[scene.nodes[i]]);
    }
}

/*
* Bind the VAO for drawing, returns the appropriate Pre-Transform
* for the engine to use.
*/
float GLTFStaticMesh::prepareForDrawing() {
    glBindVertexArray(VAO_and_EBOs.first);
    return scale;
}

GLTFStaticMesh::~GLTFStaticMesh() {
    glDeleteVertexArrays(1, &VAO_and_EBOs.first);
    for (auto it = VAO_and_EBOs.second.cbegin(); it != VAO_and_EBOs.second.cend();) {
        glDeleteBuffers(1, &VAO_and_EBOs.second[it->first]);
        VAO_and_EBOs.second.erase(it++);
    }
}