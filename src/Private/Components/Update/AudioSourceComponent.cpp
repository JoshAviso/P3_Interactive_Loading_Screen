#include <Components/Update/AudioSourceComponent.h>

#include <Core/Logger.h>
#include <Core/String.h>

AudioSourceComponent::AudioSourceComponent(String musicFilePath)
{
	if (!SetMusic(musicFilePath)) {
		Logger::LogWarning("AudioSourceComponent failed to load music from file: " + musicFilePath);
	}
}

AudioSourceComponent::AudioSourceComponent(Shared<SoundClipResource> soundclip)
{
	SetSoundClip(soundclip);
}

AudioSourceComponent::~AudioSourceComponent()
{
	_music.stop();
	_sound.stop();
}

void AudioSourceComponent::Play()
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) { _music.play(); return; }
	if (_soundclipResource != nullptr) { _sound.play(); return; }

	Logger::LogWarning("No music or sound clip set to play on audio source.");
}

void AudioSourceComponent::Pause()
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) { _music.pause(); return; }
	if (_soundclipResource != nullptr) { _sound.pause(); return; }

	Logger::LogWarning("No music or sound clip set on audio source.");
}

void AudioSourceComponent::Stop()
{
	_music.stop();
	_sound.stop();
	_soundclipResource.reset();
}

bool AudioSourceComponent::SetMusic(String musicFilePath)
{
	Stop();

	if (!_music.openFromFile(musicFilePath)) {
		Logger::LogWarning("Failed to load music from file: " + musicFilePath);
		return false;
	}

	_musicFilePath = musicFilePath;
	_soundclipResource.reset();

	return true;
}

void AudioSourceComponent::SetSoundClip(Shared<SoundClipResource> soundclip)
{
	Stop();

	if (soundclip == nullptr) {
		Logger::LogWarning("Null sound clip resource provided to audio source.");
		return;
	}

	_sound.setBuffer(soundclip->_sound);
	_soundclipResource = soundclip;
	_musicFilePath = String();
}

void AudioSourceComponent::SetVolume(float volume)
{
	_music.setVolume(volume * 100.f);
	_sound.setVolume(volume * 100.f);
}

void AudioSourceComponent::SetPitch(float pitch)
{
	_music.setPitch(pitch);
	_sound.setPitch(pitch);
}

void AudioSourceComponent::SetLooping(bool loop)
{
	_music.setLoop(loop);
	_sound.setLoop(loop);
}

void AudioSourceComponent::SetStartTimeOffset(float time)
{
	_music.setPlayingOffset(sf::seconds(time));
	_sound.setPlayingOffset(sf::seconds(time));
}

float AudioSourceComponent::GetVolume() const
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) {
		return _music.getVolume() / 100.f;
	}
	if (_soundclipResource != nullptr) {
		return _sound.getVolume() / 100.f;
	}

	return -1.f;
}

float AudioSourceComponent::GetPitch() const
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) {
		return _music.getPitch();
	}
	if (_soundclipResource != nullptr) {
		return _sound.getPitch();
	}

	return -1.f;
}

bool AudioSourceComponent::IsLooping() const
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) {
		return _music.getLoop();
	}
	if (_soundclipResource != nullptr) {
		return _sound.getLoop();
	}

	return false;
}

float AudioSourceComponent::GetPlaybackOffset() const
{
	if (!IsEmptyOrWhitespace(_musicFilePath)) {
		return _music.getPlayingOffset().asSeconds();
	}
	if (_soundclipResource != nullptr) {
		return _sound.getPlayingOffset().asSeconds();
	}

	return -1.f;
}

String AudioSourceComponent::GetMusicFilePath() const
{
	return _musicFilePath;
}

Shared<SoundClipResource> AudioSourceComponent::GetSoundClip() const
{
	return _soundclipResource;
}

void AudioSourceComponent::Update(float deltaTime)
{

}
