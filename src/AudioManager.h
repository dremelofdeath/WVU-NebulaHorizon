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
    virtual void loadSFX(const char* sfxFilename);
    virtual void playSFX(const char* sfxFilename);
    virtual bool isSFXLoaded(const char* sfxFilename);
    virtual void playMusic(const char* musicFilename);
    virtual void stopMusic();
  private:
    static AudioManager* _singleton;
};

#endif
