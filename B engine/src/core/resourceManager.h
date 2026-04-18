#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "../Renderer/IRenderer.h"
#include "../core/IAudio.h"
#include "types.h"
#include "font.h"
#include "core/MemoryTracker.h"

namespace Engine
{
    class ResourceManager
    {
    public:
        /// @param renderer  Renderer interface used to load GPU-side resources.
        /// @param audio     Audio interface used to load sound data (may be null if audio is disabled).
        ResourceManager(IRenderer* renderer, IAudio* audio = nullptr);
        ~ResourceManager();

        ResourceManager(const ResourceManager&)            = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        /// Returns a cached texture, loading it on first request. Falls back to NoTexture.png.
        Texture2D GetTexture(const std::string& filepath);

        /// Returns a 1x1 white pixel texture (used internally as a fallback).
        Texture2D GetWhitePixel();

        /// Creates and tracks a render texture at the given pixel size.
        RenderTexture2D CreateRenderTexture(const Vector2i& size);

        /// Returns a cached font atlas, loading it on first request.
        Font* GetFont(const std::string& filepath, int fontSize);

        /// Returns a cached audio clip, loading it on first request.
        /// Returns an invalid clip (id == 0) if audio is not available.
        AudioClip GetAudioClip(const std::string& filepath);

        /// Unloads all resources and releases GPU/audio memory.
        void Clear();

    private:
        IRenderer* renderer;
        IAudio*    audio;

        std::unordered_map<std::string, Texture2D>   textures;
        std::unordered_map<std::string, Font*>        fonts;
        std::unordered_map<std::string, AudioClip>    audioClips;
        std::vector<RenderTexture2D>                  renderTextures;
    };
}
