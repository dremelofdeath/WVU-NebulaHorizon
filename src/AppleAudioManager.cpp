/*
 *  AppleAudioManager.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/9/09.
 *
 */

#ifdef __APPLE__

#include "AppleAudioManager.h"

void AppleAudioManager::loadSFX(const char* sfxFilename) {
    if(!isSFXLoaded(sfxFilename)) {
        SystemSoundID ssid;
        CFStringRef strref = CFStringCreateWithCString(
            kCFAllocatorDefault,
            sfxFilename,
            kCFStringEncodingUTF8
        );
        CFURLRef ref = CFURLCreateWithFileSystemPath(
            kCFAllocatorDefault,
            strref,
            kCFURLPOSIXPathStyle,
            FALSE
        );
        AudioServicesCreateSystemSoundID(ref, &ssid);
        _loadedSounds[sfxFilename] = ssid;
    }
}

void AppleAudioManager::playSFX(const char* sfxFilename) {
    loadSFX(sfxFilename);
    AudioServicesPlaySystemSound(_loadedSounds[sfxFilename]);
}

bool AppleAudioManager::isSFXLoaded(const char* sfxFilename) {
    return _loadedSounds[sfxFilename] != 0;
}

void AppleAudioManager::playMusic(const char* musicFilename) {
    // TODO: do nothing at the moment
}

void AppleAudioManager::stopMusic() {
    // TODO: do nothing at the moment
}

#endif
