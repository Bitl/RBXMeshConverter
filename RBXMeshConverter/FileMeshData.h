#include "MeshFileStructs.h"

#include <vector>
#include <ostream>

namespace RBX
{
	struct FileMeshData
	{
		std::vector<FileMeshVertexNormalTexture3d> vnts;
		std::vector<FileMeshFace> faces;
		// G3D::AABox aabb;
	};

	void writeFileMesh(std::ostream&, const FileMeshData&);
}
