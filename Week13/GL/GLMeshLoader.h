#pragma once

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

#include <gl/glm/glm.hpp>

#include "GLMesh.h"

class GLMeshLoader
{
public:
	static GLSharedPtr<GLMesh> Load(const std::string filePath)
	{
		if (loadedMeshes.find(filePath) != loadedMeshes.end())
		{
			return loadedMeshes[filePath];
		}

		FILE* file = fopen(filePath.c_str(), "r");
		if (file == NULL) {
			return nullptr;
		}	

		auto mesh = GLCreate<GLMesh>();

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

				vertices.push_back(vertex);
				mesh->AddVertex(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				
				uv.y = -uv.y;
				uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

				normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					fclose(file);
					return nullptr;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else {
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}

		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];


			// Put the attributes in buffers
			mesh->AddNormal(normals[normalIndex - 1]);
			mesh->AddUV(uvs[uvIndex - 1]);
			mesh->AddIndex(vertexIndex - 1);
		}

		fclose(file);

		loadedMeshes[filePath] = mesh;

		return mesh;
	}
private:
	static std::unordered_map<std::string, GLSharedPtr<GLMesh>> loadedMeshes;
};

std::unordered_map<std::string, GLSharedPtr<GLMesh>> GLMeshLoader::loadedMeshes;