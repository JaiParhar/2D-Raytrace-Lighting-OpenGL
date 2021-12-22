#include "load.h"

std::vector<unsigned char> loadFileToCharBuffer(const char* filename)
{
	std::vector<unsigned char> buffer;
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

    //get filesize
    std::streamsize size = 0;
    if (file.seekg(0, std::ios::end).good()) size = file.tellg();
    if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

    //read contents of the file into the vector
    if (size > 0)
    {
        buffer.resize((size_t)size);
        file.read((char*)(&buffer[0]), size);
    }
    else buffer.clear();

	return buffer;
}

std::string loadFileToString(const char* file_path) {

	std::string fileString;
	std::ifstream fileStringStream(file_path, std::ios::in);
	if (fileStringStream.is_open()) {
		std::stringstream sstr;
		sstr << fileStringStream.rdbuf();
		fileString = sstr.str();
		fileStringStream.close();
	}
	else {
		printf("Could not open %s.\n", file_path);
	}

	return fileString;
}