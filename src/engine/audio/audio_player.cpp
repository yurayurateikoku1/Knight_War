#include "audio_player.h"
#include "../resource/resource_manager.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

engine::audio::AudioPlayer::AudioPlayer(engine::resource::ResourceManager *resource_manager)
    : resource_manager_(resource_manager)
{
    if (!resource_manager_)
    {
        throw std::runtime_error("ResourceManager is nullptr");
    }
    mixer_ = resource_manager_->getMixer();
    if (!mixer_)
    {
        throw std::runtime_error("MIX_Mixer is nullptr");
    }
}

engine::audio::AudioPlayer::~AudioPlayer()
{
    if (musicTrack_)
    {
        MIX_StopTrack(musicTrack_, 0);
        MIX_DestroyTrack(musicTrack_);
        musicTrack_ = nullptr;
    }
    if (soundTrack_)
    {
        MIX_StopTrack(soundTrack_, 0);
        MIX_DestroyTrack(soundTrack_);
        soundTrack_ = nullptr;
    }
    if (musicAudio_)
    {
        MIX_DestroyAudio(musicAudio_);
        musicAudio_ = nullptr;
    }
    if (soundAudio_)
    {
        MIX_DestroyAudio(soundAudio_);
        soundAudio_ = nullptr;
    }
}

int engine::audio::AudioPlayer::playSound(const std::string &sound_path, int channel)
{
    MIX_Audio *audio = resource_manager_->loadSound(sound_path);
    if (!audio)
    {
        return -1;
    }

    if (!soundTrack_)
    {
        soundTrack_ = MIX_CreateTrack(mixer_);
        if (!soundTrack_)
        {
            spdlog::error("Failed to create sound track: {}", SDL_GetError());
            return -1;
        }
    }

    if (soundAudio_)
    {
        MIX_DestroyAudio(soundAudio_);
        soundAudio_ = nullptr;
    }

    soundAudio_ = MIX_LoadAudio(mixer_, sound_path.c_str(), false);
    if (!soundAudio_)
    {
        spdlog::error("Failed to reload sound audio: {}", SDL_GetError());
        return -1;
    }

    if (!MIX_SetTrackAudio(soundTrack_, soundAudio_))
    {
        spdlog::error("Failed to set track audio: {}", SDL_GetError());
        return -1;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, 0);

    if (!MIX_PlayTrack(soundTrack_, props))
    {
        spdlog::error("Failed to play sound track: {}", SDL_GetError());
        SDL_DestroyProperties(props);
        return -1;
    }

    SDL_DestroyProperties(props);
    spdlog::info("Playing sound: {}", sound_path);
    return 0;
}

int engine::audio::AudioPlayer::playMusic(const std::string &music_path, int loops, int fade_in_ms)
{
    if (music_path == current_music_)
    {
        return true;
    }
    current_music_ = music_path;
    if (!musicTrack_)
    {
        musicTrack_ = MIX_CreateTrack(mixer_);
        if (!musicTrack_)
        {
            spdlog::error("Failed to create music track: {}", SDL_GetError());
            return -1;
        }
    }

    if (musicAudio_)
    {
        MIX_DestroyAudio(musicAudio_);
        musicAudio_ = nullptr;
    }

    musicAudio_ = MIX_LoadAudio(mixer_, music_path.c_str(), true);
    if (!musicAudio_)
    {
        spdlog::error("Failed to load music: {}", SDL_GetError());
        return -1;
    }

    if (!MIX_SetTrackAudio(musicTrack_, musicAudio_))
    {
        spdlog::error("Failed to set track audio: {}", SDL_GetError());
        return -1;
    }

    MIX_SetTrackGain(musicTrack_, 0.05f);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
    if (fade_in_ms > 0)
    {
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fade_in_ms);
    }

    if (!MIX_PlayTrack(musicTrack_, props))
    {
        spdlog::error("Failed to play music track: {}", SDL_GetError());
        SDL_DestroyProperties(props);
        return -1;
    }

    SDL_DestroyProperties(props);
    current_music_ = music_path;
    spdlog::info("Playing music: {}", music_path);
    return 0;
}

void engine::audio::AudioPlayer::stopMusic(int fade_out_ms)
{
    if (musicTrack_)
    {
        MIX_StopTrack(musicTrack_, fade_out_ms);
    }
}

void engine::audio::AudioPlayer::pauseMusic()
{
    if (musicTrack_)
    {
        MIX_PauseTrack(musicTrack_);
    }
}

void engine::audio::AudioPlayer::resumeMusic()
{
    if (musicTrack_)
    {
        MIX_ResumeTrack(musicTrack_);
    }
}

void engine::audio::AudioPlayer::setSoundVolume(float volume, int channel)
{
    if (soundTrack_)
    {
        MIX_SetTrackGain(soundTrack_, volume);
    }
}

void engine::audio::AudioPlayer::setMusicVolume(float volume)
{
    if (musicTrack_)
    {
        MIX_SetTrackGain(musicTrack_, volume);
    }
}

float engine::audio::AudioPlayer::getMusicVolume()
{
    if (musicTrack_)
    {
        return MIX_GetTrackGain(musicTrack_);
    }
    return 0.0f;
}

float engine::audio::AudioPlayer::getSoundVolume(int channel)
{
    if (soundTrack_)
    {
        return MIX_GetTrackGain(soundTrack_);
    }
    return 0.0f;
}
