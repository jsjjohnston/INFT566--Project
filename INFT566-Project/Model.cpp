#include "Model.h"

Model::Model()
{
	std::string err;
	bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &err, "./Models/Bunny.obj");
	
	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	m_glInfo.resize(shapes.size());
	// grab each shape
	int shapeIndex = 0;
	for (auto& shape : shapes) {
		// setup OpenGL data
		glGenVertexArrays(1, &m_glInfo[shapeIndex].m_VAO);
		glGenBuffers(1, &m_glInfo[shapeIndex].m_VBO);
		glBindVertexArray(m_glInfo[shapeIndex].m_VAO);

		m_glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size();
		// collect triangle vertices
		std::vector<OBJVertex> vertices;
		int index = 0;
		for (auto face : shape.mesh.num_face_vertices) {
			for (int i = 0; i < 3; ++i) {
				tinyobj::index_t idx = shape.mesh.indices[index + i];
				OBJVertex v = { 0 };
				// positions
				v.x = attribs.vertices[3 * idx.vertex_index + 0];
				v.y = attribs.vertices[3 * idx.vertex_index + 1];
				v.z = attribs.vertices[3 * idx.vertex_index + 2];
				// normals
				if (attribs.normals.size() > 0) {
					v.nx = attribs.normals[3 * idx.normal_index + 0];
					v.ny = attribs.normals[3 * idx.normal_index + 1];
					v.nz = attribs.normals[3 * idx.normal_index + 2];
				}
				// texture coordinates
				if (attribs.texcoords.size() > 0) {
					v.u = attribs.texcoords[2 * idx.texcoord_index + 0];
					v.v = attribs.texcoords[2 * idx.texcoord_index + 1];
				}
				vertices.push_back(v);
			}
			index += face;
		}
		// bind vertex data
		glBindBuffer(GL_ARRAY_BUFFER, m_glInfo[shapeIndex].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex),
			vertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0); //position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(OBJVertex), 0);
		glEnableVertexAttribArray(1); //normal data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE,
			sizeof(OBJVertex), (void*)12);
		glEnableVertexAttribArray(2); //texture data
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(OBJVertex), (void*)24);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shapeIndex++;
	}
}


Model::~Model()
{
}
