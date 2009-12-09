/*
 *  AudioManager.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/9/09.
 *
 */

#ifndef NHZ_AUDIOMANAGER_H
#define NHZ_AUDIOMANAGER_H

class AudioManager {
    public:
        static AudioManager* const getInstance();
        virtual void loadSFX(const char* sfxFilename) = 0;
        virtual void playSFX(const char* sfxFilename) = 0;
        virtual bool isSFXLoaded(const char* sfxFilename) = 0;
        virtual void playMusic(const char* musicFilename) = 0;
        virtual void stopMusic() = 0;
    private:
        static AudioManager* _singleton;
};

#endif
