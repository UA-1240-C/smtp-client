#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace ISXUtilities
{
    constexpr inline size_t MAX_FILE_SIZE = 5 * 1024 * 1024;
    constexpr inline size_t CHUNK_SIZE = 72;

    size_t FileSize(const std::filesystem::path& path);
    bool OpenFile(const std::string& filename, std::ifstream& file);
}