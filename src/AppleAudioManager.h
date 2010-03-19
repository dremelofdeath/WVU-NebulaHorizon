/*
 *  AppleAudioManager.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/9/09.
 *
 */

#ifndef __APPLE__
#error "Inclusion of Apple-specific header on non-Apple platform."
#else

#ifndef NHZ_APPLEAUDIOMANAGER_H
#define NHZ_APPLEAUDIOMANAGER_H

#include <map>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/AudioToolbox.h>
#include "AudioManager.h"

class AppleAudioManager : public AudioManager {
  public:
    void loadSFX(const char* sfxFilename);
    void playSFX(const char* sfxFilename);
    bool isSFXLoaded(const char* sfxFilename);
    void playMusic(const char* musicFilename);
    void stopMusic();
  private:
    std::map<const char*, SystemSoundID> _loadedSounds;
};

#endif

#endif
