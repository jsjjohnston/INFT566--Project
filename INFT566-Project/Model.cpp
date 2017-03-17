#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

Model::Model(): m_position(0), m_rotation(0)
{
}


Model::~Model()
{
}

bool Model::loadModel(const char * a_fileName)
{
	// tinyOBJ Required Parameters
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err; // Errors Warning Messages

	bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &err, a_fileName, "");

	/*
		Err could contain warning messages
	*/
	if (!err.empty())
	{
		std::cout << err << std::endl; // Output errors and Warnaings
	}

	// if model load Failed return false
	if (!success)
		return false;

	// Output number of shapes and Materials
	std::cout << "# of Shapes    : " << shapes.size() << std::endl;
	std::cout << "# of Materials : " << materials.size() << std::endl;

	std::cout << "# of Texcoords : " << attribs.texcoords.size() << std::endl;

	m_glInfo.resize(shapes.size());

	// For Each Shape
	int shapeIndex = 0;
	for (auto& shape : shapes)
	{
		// Setup OpenGL Data
		glGenBuffers(1, &m_glInfo[shapeIndex].m_VBO);
		glGenVertexArrays(1, &m_glInfo[shapeIndex].m_VAO);
		glBindVertexArray(m_glInfo[shapeIndex].m_VAO);

		// Set number of face vertices
		m_glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size();

		// Collect Triangle Vertices
		std::vector<OBJVertex> vertices;
		int index = 0;

		for (auto face : shape.mesh.num_face_vertices)
		{
			for (int i = 0; i < 3; i++)
			{
				tinyobj::index_t idx = shape.mesh.indices[index + i];

				OBJVertex vertex;
				
				//Collect Positions
				vertex.position.x = attribs.vertices[3 * idx.vertex_index + 0];
				vertex.position.y = attribs.vertices[3 * idx.vertex_index + 1];
				vertex.position.z = attribs.vertices[3 * idx.vertex_index + 2];

				//Collect Normals
				if (attribs.normals.size() > 0) // Check if obj Has Normals 
				{
					vertex.normal.x = attribs.normals[3 * idx.normal_index + 0];
					vertex.normal.y = attribs.normals[3 * idx.normal_index + 1];
					vertex.normal.z = attribs.normals[3 * idx.normal_index + 2];
				}
				
				//Collect texture coordinates
				if (attribs.texcoords.size() > 0)
				{
					vertex.u = attribs.texcoords[2 * idx.texcoord_index + 0]; 
					vertex.v = -attribs.texcoords[2 * idx.texcoord_index + 1];
				}
				vertices.push_back(vertex);
			}
			index += face;
		}

		// Bind Vertex data
		glBindBuffer(GL_ARRAY_BUFFER, m_glInfo[shapeIndex].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex),vertices.data(), GL_STATIC_DRAW);
		
		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0);
		//Normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)12);
		//Texture Data
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)24);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shapeIndex++;
	}

	return success;
}

void Model::update(float a_deltaTime)
{
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_position.z -= DEFAULT_MODEL_MOVMENT + a_deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS)
		m_position.z += DEFAULT_MODEL_MOVMENT + a_deltaTime;

	m_rotation += DEFAULT_MODEL_ROTATION + a_deltaTime;

	glm::mat4 modelTransform = glm::translate(m_position) * glm::rotate(m_rotation, glm::vec3(0,1,0));
	glm::mat4 fullFransform = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f) *	m_camera->getWorldToViewMatrix() * modelTransform;

	m_program->setUniform("modelToProjectionMatrix", fullFransform);
	m_program->setUniform("modelToWorldTransformMatrix", modelTransform);

	//TODO Get [Texturing] Working
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	int loc = glGetUniformLocation(m_program->getHandle(), "diffuse");
	glUniform1i(loc, 0);
}

void Model::draw()
{
	for (auto& gl : m_glInfo)
	{
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	}
}

void Model::loadDiffuseTexture(const char* a_fileName)
{
	// Image Data //TODO Get [Texturing] Working
	int imageWidth = 0;
	int imageHeight = 0;
	int imageFormat = 0;

	// Get Image Data //TODO Get [Texturing] Working
	unsigned char* data = stbi_load(a_fileName, &imageWidth, &imageHeight, &imageFormat, STBI_default);

	// Load Image data on to the GFX card //TODO Get [Texturing] Working
	glGenTextures(1, &m_DiffuseTexture);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data); // Free Image Data
}
