#include "File.h"

namespace ISXUtilities
{
    size_t FileSize(const std::filesystem::path& path)
    {
        return std::filesystem::file_size(path);
    }

    bool OpenFile(const std::string& filename, std::ifstream& file)
    {
        file.open(filename, std::ios::binary);
        
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }
        else if (FileSize(filename) > MAX_FILE_SIZE)
        {
            std::cerr << "File is too big" << std::endl;
            return false;
        }

        return true;
        
    }
}