#pragma once

namespace RBX
{
	struct FileMeshHeader
	{
		unsigned short cbSize;
		unsigned char cbVerticesStride;
		unsigned char cbFaceStride;

		unsigned int numVertices;
		unsigned int numFaces;
	};

	struct FileMeshVertexNormalTexture3d
	{
		float vx, vy, vz;
		float nx, ny, nz;
		float tu, tv, tw;
		// char r, g, b, a;
	};

	struct FileMeshFace
	{
		unsigned int a;
		unsigned int b;
		unsigned int c;
	};
}
