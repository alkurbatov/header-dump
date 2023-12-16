#include <fstream>
#include <iostream>
#include <string>

std::string readString(std::ifstream& src, int size)
{
    std::string buf(size, '\0');
    src.read(&buf[0], buf.size());

    return buf;
}

template <typename T>
T readNumber(std::ifstream& src)
{
    T buf;
    src.read(reinterpret_cast<char*>(&buf), sizeof(T));

    return buf;
}

std::string readChunkName(std::ifstream& src)
{
    return readString(src, 4);
}

uint32_t readChunkSize(std::ifstream& src)
{
    return readNumber<std::uint32_t>(src);
}

void readHeaderChunk(std::ifstream& src)
{
    std::cout << readString(src, 4) << '\n';
}

void readFormatChunk(std::ifstream& src)
{
    auto formatCode = readNumber<std::uint16_t>(src);
    std::cout << "format code: " << formatCode << '\n';
    std::cout << "channels: " << readNumber<std::uint16_t>(src) << '\n';
    std::cout << "sample rate: " << readNumber<std::uint32_t>(src) << '\n';
    std::cout << "byte rate: " << readNumber<std::uint32_t>(src) << '\n';
    std::cout << "block align: " << readNumber<std::uint16_t>(src) << '\n';
    std::cout << "bit depth: " << readNumber<std::uint16_t>(src) << '\n';

    if (formatCode == 6 || formatCode == 7)  // A-law or (M)u-law
        std::cout << "extension size: " << readNumber<std::uint16_t>(src) << '\n';
}

void readFactChunk(std::ifstream& src)
{
    std::cout << "sample length: " << readNumber<std::uint32_t>(src) << '\n';
}

void readListChunk(std::ifstream& src)
{
    std::cout << readString(src, 4) << '\n';
    std::cout << readString(src, 4) << ": " << readString(src, 18) << '\n';
}

int main(int /* argc */, char** argv)
{
    std::ifstream src{argv[1], std::ios::binary};

    while (true)
    {
        std::cout << '\n';

        auto chunkName = readChunkName(src);
        auto chunkSize = readChunkSize(src);

        std::cout << "Chunk: " << chunkName << '\n';
        std::cout << "size: " << chunkSize << '\n';

        if (chunkName == "RIFF")
        {
            readHeaderChunk(src);
            continue;
        }

        if (chunkName == "fmt ")
        {
            readFormatChunk(src);
            continue;
        }

        if (chunkName == "fact")
        {
            readFactChunk(src);
            continue;
        }

        if (chunkName == "LIST")
        {
            readListChunk(src);
            continue;
        }

        if (chunkName == "data")
            return 0;
    }

    return 0;
}
