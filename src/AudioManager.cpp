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
#ifdef __APPLE__
    _singleton = new AppleAudioManager();
#elif WIN32
#pragma message ("WARNING: Audio is not yet supported on this platform.")
#elif
#warning "Audio is not yet supported on this platform."
#endif
  }
  return _singleton;
}
