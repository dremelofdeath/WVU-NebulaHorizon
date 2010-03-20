/*
 *  AudioManager.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/9/09.
 *
 */

#ifdef __APPLE__
#include "AppleAudioManager.h"
#endif

#include "AudioManager.h"

AudioManager* AudioManager::_singleton = 0;

AudioManager* const AudioManager::getInstance() {
  if(_singleton == 0) {
    _singleton =
#ifdef __APPLE__
      new AppleAudioManager();
#else // platform not supported
#ifdef WIN32
#pragma message ("WARNING: Audio is not yet supported on this platform.")
#elif
#warning "Audio is not yet supported on this platform."
#endif
      new AudioManager(); // null driver, does nothing
#endif
  }
  return _singleton;
}

void AudioManager::loadSFX(const char* sfxFilename) {
  // do nothing
}

void AudioManager::playSFX(const char* sfxFilename) {
  // do nothing
}

bool AudioManager::isSFXLoaded(const char* sfxFilename) {
  // always say yes to continue program flow (won't play anyway)
  return 1;
}

void AudioManager::playMusic(const char* musicFilename) {
  // do nothing
}

void AudioManager::stopMusic() {
  // do nothing
}
