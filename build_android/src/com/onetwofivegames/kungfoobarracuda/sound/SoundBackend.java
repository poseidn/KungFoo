package com.onetwofivegames.kungfoobarracuda.sound;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;

import com.onetwofivegames.kungfoobarracuda.JavaLog;
import com.onetwofivegames.kungfoobarracuda.exceptions.ResourceNotFound;

import java.util.HashMap;
import java.util.Map;

/*
 * short samples can be played via the sound pool which allows the same
 * sample to be played multiple times
 * longer parts ( like music ) must be player via the MediaPlayer because
 * they don't fit into the sound pool
 */
public class SoundBackend {

	static int Mute = 0;
	static String TAG = "SoundBackend";
	static int MaxMixerChannels = 8;

	public SoundBackend(Context ctx) {
		m_soundPool = new SoundPool(MaxMixerChannels,
				AudioManager.STREAM_MUSIC, 0);
		m_context = ctx;
	}

	class Music {
		public void play() {
			m_player.start();
		}

		public void addMedialPlayer(MediaPlayer mp) {
			m_player = mp;
		}

		public MediaPlayer getMediaPlayer() {
			return m_player;
		}

		public void setWasRunning(boolean b) {
			m_wasRuninng = b;
		}

		public boolean wasRunning() {
			return m_wasRuninng;
		}

		private MediaPlayer m_player;
		private boolean m_wasRuninng = false;
	}

	class Sample {
		Sample(int id) {
			m_id = id;
		}

		public int getId() {
			return m_id;
		}

		private int m_id;
	}

	// preloading of sound samples, can be used for large samples,
	// which would otherwise interrupte the game fps because loading takes
	// too long
	public void preloadSound(String name) throws ResourceNotFound {
		if (!m_samples.containsKey(name)) {

			int ident = m_context.getResources().getIdentifier(name, "raw",
					m_context.getPackageName());
			if (ident == 0) {
				throw new ResourceNotFound("sound " + name);
			}

			int sndId = m_soundPool.load(m_context, ident, 1);
			Sample sp = new Sample(sndId);

			m_samples.put(name, sp);

			JavaLog.info(TAG, "Sample with name " + name
					+ " has been preloaded");
		}
	}

	// preloading of music samples, can be used for large samples,
	// which would otherwise interrupte the game fps because loading takes
	// too long
	public void preloadMusic(String name) throws ResourceNotFound {
		if (!m_music.containsKey(name)) {

			int ident = m_context.getResources().getIdentifier(name, "raw",
					m_context.getPackageName());
			if (ident == 0) {
				JavaLog.fatal(TAG, "Music with name " + name
						+ " cannot be preloaded");
				throw new ResourceNotFound("music " + name);
			}

			Music sp = new Music();
			MediaPlayer mediaPlayer = MediaPlayer.create(m_context, ident);
			sp.addMedialPlayer(mediaPlayer);

			m_music.put(name, sp);
			JavaLog.info(TAG, "Music with name " + name + " has been preloaded");
		}
	}

	public int playMusic(String name) throws ResourceNotFound {
		preloadSound(name);
		if (!m_music.containsKey(name)) {
			JavaLog.fatal(TAG, "Music with name " + name + " not found");
		} else {
			Music ms = m_music.get(name);
			if (Mute == 0) {
				ms.play();
			}
		}
		// todo: no play ids supported, yet
		return 0;
	}

	public int playSound(String name, float direction) throws ResourceNotFound {
		preloadSound(name);
		if (!m_samples.containsKey(name)) {
			JavaLog.fatal(TAG, "Sound with name " + name + " not found");
			return 0;
		} else {
			Sample sp = m_samples.get(name);

			// both in the midle will be both 0.5f .. onyl half the maximum
			// volume ...
			float norm = (direction + 1.0f) * 0.5f;

			int playId = 0;

			if (Mute == 0) {
				// cool, do panning here, depending on where the player hits !
				playId = m_soundPool.play(sp.getId(), 1.0f - norm, norm, 0, 0,
						1.0f);
			}
			JavaLog.info(TAG, "Start playing sound " + playId);

			return playId;
		}
	}

	public void stopPlay(int playId) {
		JavaLog.info(TAG, "Stop playing sound " + playId);

		if (Mute == 0) {
			m_soundPool.stop(playId);
		}
	}

	public void pauseSound() {
		// stop all samples
		m_soundPool.autoPause();

		// stop all music
		for (Map.Entry<String, Music> entry : m_music.entrySet()) {
			Music ms = entry.getValue();
			MediaPlayer mplay = ms.getMediaPlayer();
			ms.setWasRunning(false);

			if (mplay.isPlaying()) {
				ms.setWasRunning(true);
				mplay.stop();
			}
		}
	}

	public void resumeSound() {
		m_soundPool.autoResume();

		// restart music
		for (Map.Entry<String, Music> entry : m_music.entrySet()) {
			Music ms = entry.getValue();
			MediaPlayer mplay = ms.getMediaPlayer();
			if (ms.wasRunning()) {
				ms.setWasRunning(false);
				mplay.start();
			}
		}
	}

	@SuppressWarnings("serial")
	private class MusicMap extends HashMap<String, Music> {
	};

	@SuppressWarnings("serial")
	private class SampleMap extends HashMap<String, Sample> {
	};

	private MusicMap m_music = new MusicMap();
	private SampleMap m_samples = new SampleMap();
	private SoundPool m_soundPool = null;
	private Context m_context = null;
	
}
