/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/asset_manager.h"
#include "glm/vec2.hpp"

#include <fmt/format.h>
#include <glm/vec3.hpp>
#include <stb_image/stb_image.h>

#include <stdexcept>
#include <fstream>
#include <sstream>

namespace ProtonEngine::Core
{

static auto splitString(std::string_view input, char delimiter = ' ') -> std::vector<std::string>
{
    std::vector<std::string> substrings;
    size_t pos = 0;

    while (true)
    {
        const auto newPos  = input.find(delimiter, pos);
        substrings.emplace_back(input.substr(pos, newPos - pos));

        if(newPos == std::string_view::npos)
            break;

        pos = newPos + 1;
    }

    return substrings;
}

Assets::Image AssetManager::readImageFromFile(std::string_view path)
{
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc * data = stbi_load(path.data(), &width, &height, &channels, 0);

    if(data == nullptr)
        throw std::runtime_error(fmt::format("Something went wrong when loading image at :{}\n", path));

    const auto image = Assets::Image(data, width, height, channels);

    stbi_image_free(data);

    return image;
}

Assets::Model AssetManager::loadModel(std::string_view path)
{
    if (path.contains(".obj"))
    {
        return loadObjModel(path);
    }

    throw std::runtime_error("Only obj models are currently supported");
}

Assets::Model AssetManager::loadObjModel(std::string_view path)
{
    const auto fileContents = [&]() -> std::string
    {
        std::ifstream inputFile(path.data());
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        return buffer.str();
    }();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;

    std::vector<float> modelVertices;
    std::vector<float> modelNormals;
    std::vector<float> modelTextureCoords;

    std::ifstream inputFile(path.data());
    std::string line;

    while(std::getline(inputFile, line))
    {
        switch(line[0])
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

            if(splittedString[0] == "v")
            {
                vertices.emplace_back(std::stof(splittedString[1]), std::stof(splittedString[2]), std::stof(splittedString[3]));
                continue;
            }

            if(splittedString[0] == "vn")
            {
                normals.emplace_back(std::stof(splittedString[1]), std::stof(splittedString[2]), std::stof(splittedString[3]));
                continue;
            }

            if(splittedString[0] == "vt")
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

            const auto vertex1 = vertices[std::stoi(splitPoint1Data[0]) - 1];
            const auto vertex2 = vertices[std::stoi(splitPoint2Data[0]) - 1];
            const auto vertex3 = vertices[std::stoi(splitPoint3Data[0]) - 1];

            const auto texture1 = textureCoords[std::stoi(splitPoint1Data[1]) - 1];
            const auto texture2 = textureCoords[std::stoi(splitPoint2Data[1]) - 1];
            const auto texture3 = textureCoords[std::stoi(splitPoint3Data[1]) - 1];

            const auto normal1 = normals[std::stoi(splitPoint1Data[2]) - 1];
            const auto normal2 = normals[std::stoi(splitPoint2Data[2]) - 1];
            const auto normal3 = normals[std::stoi(splitPoint3Data[2]) - 1];

            modelVertices.emplace_back(vertex1.x);
            modelVertices.emplace_back(vertex1.y);
            modelVertices.emplace_back(vertex1.z);
            modelVertices.emplace_back(vertex2.x);
            modelVertices.emplace_back(vertex2.y);
            modelVertices.emplace_back(vertex2.z);
            modelVertices.emplace_back(vertex3.x);
            modelVertices.emplace_back(vertex3.y);
            modelVertices.emplace_back(vertex3.z);

            modelNormals.emplace_back(normal1.x);
            modelNormals.emplace_back(normal1.y);
            modelNormals.emplace_back(normal1.z);
            modelNormals.emplace_back(normal2.x);
            modelNormals.emplace_back(normal2.y);
            modelNormals.emplace_back(normal2.z);
            modelNormals.emplace_back(normal3.x);
            modelNormals.emplace_back(normal3.y);
            modelNormals.emplace_back(normal3.z);

            modelTextureCoords.emplace_back(texture1.x);
            modelTextureCoords.emplace_back(texture1.y);
            modelTextureCoords.emplace_back(texture2.x);
            modelTextureCoords.emplace_back(texture2.y);
            modelTextureCoords.emplace_back(texture3.x);
            modelTextureCoords.emplace_back(texture3.y);

            continue;
        }
        }

        throw std::runtime_error(fmt::format("Unsupported line: {}", line));
    }

    return Assets::Model{std::move(modelVertices), std::move(modelNormals), modelTextureCoords};
}

} // namespace ProtonEngine::Core