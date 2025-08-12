/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/assets/asset_manager.h"
#include "protonengine/common/logger.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <stb_image/stb_image.h>

#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ProtonEngine::Assets
{

static auto splitString(std::string_view input, char delimiter = ' ') -> std::vector<std::string>
{
    std::vector<std::string> substrings;
    size_t pos = 0;

    while (true)
    {
        const auto newPos = input.find(delimiter, pos);
        substrings.emplace_back(input.substr(pos, newPos - pos));

        if (newPos == std::string_view::npos)
            break;

        pos = newPos + 1;
    }

    return substrings;
}

Image AssetManager::readImageFromFile(std::string_view path)
{
    PROTON_LOG_INFO(std::format("Loading image file: {}", path));
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc * data = stbi_load(path.data(), &width, &height, &channels, 0);

    if (data == nullptr)
        throw std::runtime_error(std::format("Something went wrong when loading image at :{}\n", path));

    const auto image = Image(data, width, height, channels);

    stbi_image_free(data);

    return image;
}

Model AssetManager::loadModel(std::string_view path)
{
    PROTON_LOG_INFO(std::format("Loading model file: {}", path));

    if (path.contains(".obj"))
    {
        return loadObjModel(path);
    }

    PROTON_LOG_ERROR("Only obj models are currently supported");
    throw std::runtime_error("Only obj models are currently supported");
}

Model AssetManager::loadObjModel(std::string_view path)
{
    const auto fileContents = [&]() -> std::string {
        std::ifstream inputFile(path.data());
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        return buffer.str();
    }();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    std::vector<Face> faces;

    std::vector<float> modelVertices;
    std::vector<float> modelNormals;
    std::vector<float> modelTextureCoords;
    std::vector<float> modelIndices;

    std::ifstream inputFile(path.data());
    std::string line;

    while (std::getline(inputFile, line))
    {
        switch (line[0])
        {
        case '#':
        case 'o':
        case 's':
        case 'm':
        case 'u':
            continue;
        case 'v':
        {
            const auto splittedString = splitString(line);

            if (splittedString[0] == "v")
            {
                vertices.emplace_back(std::stof(splittedString[1]), std::stof(splittedString[2]), std::stof(splittedString[3]));
                continue;
            }

            if (splittedString[0] == "vn")
            {
                normals.emplace_back(std::stof(splittedString[1]), std::stof(splittedString[2]), std::stof(splittedString[3]));
                continue;
            }

            if (splittedString[0] == "vt")
            {
                textureCoords.emplace_back(std::stof(splittedString[1]), std::stof(splittedString[2]));
                continue;
            }
            continue;
        }
        case 'f':
        {
            const auto splittedFaceData = splitString(line);
            const auto splitPoint1Data = splitString(splittedFaceData[1], '/');
            const auto splitPoint2Data = splitString(splittedFaceData[2], '/');
            const auto splitPoint3Data = splitString(splittedFaceData[3], '/');

            Face face = {
                .vertexIndex = {std::stoi(splitPoint1Data[0]) - 1, std::stoi(splitPoint2Data[0]) - 1, std::stoi(splitPoint3Data[0]) - 1},
                .normalIndex = {std::stoi(splitPoint1Data[2]) - 1, std::stoi(splitPoint2Data[2]) - 1, std::stoi(splitPoint3Data[2]) - 1},
                .textureIndex = {std::stoi(splitPoint1Data[1]) - 1, std::stoi(splitPoint2Data[1]) - 1, std::stoi(splitPoint3Data[1]) - 1}};

            faces.emplace_back(face);

            continue;
        }
        }

        throw std::runtime_error(std::format("Unsupported line: {}", line));
    }

    return Model{std::move(faces), std::move(vertices), std::move(normals), std::move(textureCoords)};
}

} // namespace ProtonEngine::Assets