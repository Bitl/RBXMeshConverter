#include "FileMeshData.h"

void RBX::writeFileMesh(std::ostream& f, const FileMeshData& data)
{
	f << "version 2.00" << std::endl;
	FileMeshHeader header;
	header.numFaces = data.faces.size();
	header.numVertices = data.vnts.size();
	header.cbFaceStride = (unsigned char)sizeof(data.faces[0]);
	header.cbVerticesStride = (unsigned char)sizeof(data.vnts[0]);
	header.cbSize = sizeof(header);
	f.write(reinterpret_cast<char*>(&header), sizeof(header));

	f.write(reinterpret_cast<const char*>(&data.vnts[0]), sizeof(data.vnts[0]) * data.vnts.size());
	f.write(reinterpret_cast<const char*>(&data.faces[0]), sizeof(data.faces[0]) * data.faces.size());
}
