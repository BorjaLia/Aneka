#include "ResourceManager.h"
#include "debug.h"
#include <unordered_set>
#include <iostream>

namespace Engine
{
    ResourceManager::ResourceManager(IRenderer* renderer, IAudio* audio)
        : renderer(renderer), audio(audio)
    {}

    ResourceManager::~ResourceManager() { Clear(); }

    Texture2D ResourceManager::GetTexture(const std::string& filepath)
    {
        auto it = textures.find(filepath);
        if (it != textures.end()) return it->second;

        Texture2D tex = renderer->LoadTexture(filepath.c_str());
        if (tex.id == 0)
        {
            ENGINE_WARN("ResourceManager: '" << filepath << "' not found. Using fallback.");
            if (filepath != "res/sprites/NoTexture.png")
                tex = GetTexture("res/sprites/NoTexture.png");
            else
                tex = GetWhitePixel();
        }

        textures[filepath] = tex;
        return tex;
    }

    Texture2D ResourceManager::GetWhitePixel()
    {
        auto it = textures.find("INTERNAL_WHITE_PIXEL");
        if (it != textures.end()) return it->second;

        Texture2D px = renderer->CreateWhitePixel();
        textures["INTERNAL_WHITE_PIXEL"] = px;
        return px;
    }

    RenderTexture2D ResourceManager::CreateRenderTexture(const Vector2i& size)
    {
        RenderTexture2D rt = renderer->CreateRenderTexture(size);
        renderTextures.push_back(rt);
        return rt;
    }

    Font* ResourceManager::GetFont(const std::string& filepath, int fontSize)
    {
        std::string key = filepath + "_" + std::to_string(fontSize);
        auto it = fonts.find(key);
        if (it != fonts.end()) return it->second;

        Font* f = renderer->LoadFont(filepath.c_str(), fontSize);
        fonts[key] = f;
        return f;
    }

    AudioClip ResourceManager::GetAudioClip(const std::string& filepath)
    {
        if (!audio)
        {
            ENGINE_WARN("ResourceManager: Audio system not available.");
            return AudioClip{};
        }

        auto it = audioClips.find(filepath);
        if (it != audioClips.end()) return it->second;

        AudioClip clip = audio->LoadClip(filepath.c_str());
        if (clip.id == 0)
            ENGINE_WARN("ResourceManager: Audio clip '" << filepath << "' failed to load.");

        audioClips[filepath] = clip;
        return clip;
    }

    void ResourceManager::Clear()
    {
        std::unordered_set<unsigned int> unloaded;

        for (auto& [path, tex] : textures)
        {
            if (unloaded.find(tex.id) == unloaded.end())
            {
                renderer->UnloadTexture(tex);
                unloaded.insert(tex.id);
            }
        }
        textures.clear();

        for (auto& [key, font] : fonts)
        {
            if (font)
            {
                renderer->UnloadFont(font);
                delete font;
            }
        }
        fonts.clear();

        for (auto& rt : renderTextures)
            renderer->UnloadRenderTexture(rt);
        renderTextures.clear();

        if (audio)
        {
            for (auto& [path, clip] : audioClips)
                audio->UnloadClip(clip);
            audioClips.clear();
        }

        std::cout << "ResourceManager: All resources released.\n";
    }
}
