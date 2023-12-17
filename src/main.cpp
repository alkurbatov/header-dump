#include <fstream>
#include <iostream>
#include <string>

std::string readString(std::ifstream& src, int size)
{
    std::string buf(size, '\0');
    src.read(buf.data(), size);

    return buf;
}

template <typename T>
T readNumber(std::ifstream& src)
{
    T buf;
    src.read(reinterpret_cast<char*>(&buf), sizeof(T));

    return buf;
}

const auto read2BytesInt = readNumber<std::uint16_t>;
const auto read4BytesInt = readNumber<std::uint32_t>;

std::string readChunkName(std::ifstream& src)
{
    return readString(src, 4);
}

uint32_t readChunkSize(std::ifstream& src)
{
    return read4BytesInt(src);
}

void readHeaderChunk(std::ifstream& src)
{
    std::cout << "RIFF\n";
    std::cout << "size: " << readChunkSize(src) << '\n';
    std::cout << readString(src, 4) << '\n';
}

void readFormatChunk(std::ifstream& src)
{
    auto formatCode = read2BytesInt(src);
    std::cout << "format code: " << formatCode << '\n';
    std::cout << "channels: " << read2BytesInt(src) << '\n';
    std::cout << "sample rate: " << read4BytesInt(src) << '\n';
    std::cout << "byte rate: " << read4BytesInt(src) << '\n';
    std::cout << "block align: " << read2BytesInt(src) << '\n';
    std::cout << "bits per sample: " << read2BytesInt(src) << '\n';

    if (formatCode == 6 || formatCode == 7)  // A-law or (M)u-law
        std::cout << "extension size: " << read2BytesInt(src) << '\n';
}

void readFactChunk(std::ifstream& src)
{
    std::cout << "sample length: " << read4BytesInt(src) << '\n';
}

void readListChunk(std::ifstream& src)
{
    std::cout << readString(src, 4) << '\n';
    std::cout << readString(src, 4) << ": " << readString(src, 18) << '\n';
}

int main(int /* argc */, char** argv)
{
    // NB (alkurbatov): For more details regarding format of WAVE headers see
    // https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
    std::ifstream src{argv[1], std::ios::binary};

    auto chunkName = readChunkName(src);
    if (chunkName != "RIFF")
    {
        std::cout << "RIFF chunk not found, might be a raw file.\n";
        return 0;
    }

    readHeaderChunk(src);

    while (true)
    {
        std::cout << '\n';

        auto chunkName = readChunkName(src);
        auto chunkSize = readChunkSize(src);

        std::cout << "Chunk: " << chunkName << '\n';
        std::cout << "size: " << chunkSize << '\n';

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
