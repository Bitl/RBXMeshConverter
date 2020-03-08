#include "FileMeshData.h"
#include "tiny_obj_loader.h"

#include <iostream>
#include <fstream>

using namespace RBX;
using namespace tinyobj;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: RBXMeshConverter <file>" << std::endl;
		std::cin.get();
		return 0;
	}

	attrib_t attrib;
	std::vector<shape_t> shapes;

	if (!LoadObj(&attrib, &shapes, nullptr, nullptr, nullptr, argv[1]))
	{
		std::cout << "Failed to parse obj!" << std::endl;
		std::cin.get();
		return 0;
	}

	FileMeshData meshData;
	std::vector<FileMeshVertexNormalTexture3d> vnts;
	std::vector<FileMeshFace> faces;

	for (size_t i = 0; i < shapes.size(); ++i)
	{
		size_t offset = 0;

		for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); ++j)
		{
			uint8_t faceVertices = shapes[i].mesh.num_face_vertices[j];

			for (size_t k = 0; k < faceVertices; ++k)
			{
				index_t indices = shapes[i].mesh.indices[offset + k];

				FileMeshVertexNormalTexture3d vnt;
				vnt.vx = attrib.vertices[3 * indices.vertex_index + 0];
				vnt.vy = attrib.vertices[3 * indices.vertex_index + 1];
				vnt.vz = attrib.vertices[3 * indices.vertex_index + 2];
				vnt.nx = attrib.normals[3 * indices.normal_index + 0];
				vnt.ny = attrib.normals[3 * indices.normal_index + 1];
				vnt.nz = attrib.normals[3 * indices.normal_index + 2];
				vnt.tu = 0;
				vnt.tv = 0;
				vnt.tw = 0;

				if (attrib.texcoords.size() != 0)
				{
					vnt.tu = attrib.texcoords[2 * indices.texcoord_index + 0];
					vnt.tv = 1 - attrib.texcoords[2 * indices.texcoord_index + 1];
				}

				vnts.push_back(vnt);
			}
			FileMeshFace face;
			face.a = 3 * j + 0;
			face.b = 3 * j + 1;
			face.c = 3 * j + 2;
			faces.push_back(face);

			offset += faceVertices;
		}
	}

	meshData.vnts = vnts;
	meshData.faces = faces;

	std::ofstream result(std::string(argv[1]) + ".mesh", std::ios::binary);
	writeFileMesh(result, meshData);
	result.close();
}
