#include "MeshFileStructs.h"

#include <vector>
#include <ostream>

namespace RBX
{
	struct FileMeshData
	{
		std::vector<FileMeshVertexNormalTexture3d> vnts;
		std::vector<FileMeshFace> faces;
	};

	void writeFileMesh(std::ostream&, const FileMeshData&);
}
