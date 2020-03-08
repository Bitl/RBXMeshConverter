#include "FileMeshData.h"
#include "OBJ_Loader.h"

#include <iostream>
#include <fstream>

using namespace RBX;
using namespace objl;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: RBXMeshConverter <file>" << std::endl;
		std::cin.get();
		return 0;
	}

	std::string filename = argv[1];

	Loader objLoader;
	if (!objLoader.LoadFile(filename))
	{
		std::cout << "Failed to open obj!" << std::endl;
		std::cin.get();
		return 0;
	}

	FileMeshData meshData;
	std::vector<FileMeshVertexNormalTexture3d> vnts;
	std::vector<FileMeshFace> faces;

	for (size_t i = 0; i < objLoader.LoadedMeshes.size(); ++i)
	{
		Mesh currentMesh = objLoader.LoadedMeshes[i];

		for (size_t j = 0; j < currentMesh.Vertices.size(); ++j)
		{
			Vertex vertex = currentMesh.Vertices[j];

			FileMeshVertexNormalTexture3d vnt;
			
			vnt.vx = vertex.Position.X;
			vnt.vy = vertex.Position.Y;
			vnt.vz = vertex.Position.Z;

			vnt.nx = vertex.Normal.X;
			vnt.ny = vertex.Normal.Y;
			vnt.nz = vertex.Normal.Z;

			vnt.tu = vertex.TextureCoordinate.X;
			vnt.tv = 1 - vertex.TextureCoordinate.Y;

			vnts.push_back(vnt);
		}

		for (size_t k = 0; k < currentMesh.Indices.size(); k += 3)
		{
			FileMeshFace face;

			face.a = currentMesh.Indices[k];
			face.b = currentMesh.Indices[k + 1];
			face.c = currentMesh.Indices[k + 2];

			faces.push_back(face);
		}
	}

	meshData.vnts = vnts;
	meshData.faces = faces;

	std::ofstream result(filename + ".mesh", std::ios::binary);
	writeFileMesh(result, meshData);
	result.close();
}
