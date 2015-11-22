#pragma once

#include <DescentEngine/src/Log.h>
#include <string>
#include <jni.h>
#include <android/native_activity.h>

class JavaTools {
public:
	static jmethodID findJavaMethod(JNIEnv * env, jobject obj,
			std::string const& name, std::string const& signature) {

		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, name.c_str(), signature.c_str());
		if (mid == 0) {
			logging::Fatal() << "Java Method " << name << " with signature "
					<< signature << " not found";
			return 0;
		}
		return mid;
	}

	// Note: the returned jstring must not be freed in any way, because it
	// resides in the Java Mem space and will be handleded by the JVM mem management.
	static jstring toJavaString(JNIEnv * env, std::string const& st) {

		jstring jstr = env->NewStringUTF(st.c_str());
		if (jstr == 0) {
			logging::Fatal() << "NewStringUTF returned NULL";
			return nullptr;
		}
		return jstr;
	}

	static void toStdString(JNIEnv *env, jstring jStr, std::string & sStr) {
		if (!jStr) {
			sStr.clear();
			return;
		}

		const char *s = env->GetStringUTFChars(jStr, NULL);
		sStr = s;
		env->ReleaseStringUTFChars(jStr, s);
	}
};

/*
 * Attaches the current thread to the JNI calling thread and detaches, once
 * all JNI calls are complete. Use like this
 *
 * {
 * 		JniThreadAttachWrapper wrapper(myActivity);
 * 		.. do your JNI calls ...
 * }
 */
class JniThreadAttachWrapper {
public:

	JniThreadAttachWrapper(ANativeActivity * act) :
			m_act(act) {
		m_act->vm->AttachCurrentThread(&m_jniEnv, NULL);
	}

	~JniThreadAttachWrapper() {
		m_act->vm->DetachCurrentThread();
	}

	JNIEnv * getJNIEnv() const {
		assert(m_jniEnv);
		return m_jniEnv;
	}

private:
	ANativeActivity * m_act = nullptr;
	JNIEnv * m_jniEnv = nullptr;
};

class JavaInterface {
public:
	JavaInterface(ANativeActivity * native_activity) :
			m_native_activity(native_activity), m_valid(true) {

	}

	bool isValid() const {
		return m_valid;
	}
	/*
	 // todo: free the java string here ?
	 std::string readTextFile(std::string const& fileName) {
	 //assert(isValid());

	 logging::DebugC<logging::Categories::Default>() << "Calling readTextFile in Java";
	 jmethodID midPlayMusic = JavaTools::findJavaMethod(m_env, m_libObject, "readTextFile",
	 "(Ljava/lang/String;)Ljava/lang/String;");
	 jstring theFilename = JavaTools::toJavaString(m_env, fileName);
	 //jstring theText = JavaTools::toJavaString(m_env, "");

	 jobject result;
	 result = m_env->CallObjectMethod(m_libObject, midPlayMusic, theFilename);

	 std::string outString;
	 JavaTools::toStdString(m_env, (jstring) result, outString);

	 return outString;
	 }*/

	int playSound(std::string const& soundName, float direction) {
		int res;
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID midPlaySound = JavaTools::findJavaMethod(
					wrapper.getJNIEnv(), m_native_activity->clazz, "playSound",
					"(Ljava/lang/String;F)I");
			jstring theSoundname = JavaTools::toJavaString(wrapper.getJNIEnv(),
					soundName);
			res = wrapper.getJNIEnv()->CallIntMethod(m_native_activity->clazz,
					midPlaySound, theSoundname);
		}

		return res;
	}

	int playMusic(std::string const& musicName) {
		int res;
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID midPlayMusic = JavaTools::findJavaMethod(
					wrapper.getJNIEnv(), m_native_activity->clazz, "playMusic",
					"(Ljava/lang/String;)I");
			jstring theSoundname = JavaTools::toJavaString(wrapper.getJNIEnv(),
					musicName);
			res = wrapper.getJNIEnv()->CallIntMethod(m_native_activity->clazz,
					midPlayMusic, theSoundname);
		}
		return res;
	}

	void stopPlay(int playId, float fadeOutTime) {
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID midStopPlay = JavaTools::findJavaMethod(
					wrapper.getJNIEnv(), m_native_activity->clazz, "stopPlay",
					"(I)V");
			wrapper.getJNIEnv()->CallVoidMethod(m_native_activity->clazz,
					midStopPlay, playId);
		}
	}

	int loadImage(std::string const& imageName) {
		assert(m_valid);
		int res;
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID midLoadImage = JavaTools::findJavaMethod(
					wrapper.getJNIEnv(), m_native_activity->clazz, "loadImage",
					"(Ljava/lang/String;)I");
			jstring theImageName = JavaTools::toJavaString(wrapper.getJNIEnv(),
					imageName);
			res = wrapper.getJNIEnv()->CallIntMethod(m_native_activity->clazz,
					midLoadImage, theImageName);
		}

		return res;
	}

	void freeTexture(int textureId) {
		assert(m_valid);
		int res;
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID mid = JavaTools::findJavaMethod(wrapper.getJNIEnv(),
					m_native_activity->clazz, "freeTexture", "(I)V");
			wrapper.getJNIEnv()->CallVoidMethod(m_native_activity->clazz, mid,
					textureId);
		}
	}

	void resumeSound() {
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID mid = JavaTools::findJavaMethod(wrapper.getJNIEnv(),
					m_native_activity->clazz, "resumeSound", "()V");
			wrapper.getJNIEnv()->CallVoidMethod(m_native_activity->clazz, mid);
		}
	}

	void pauseSound() {
		{
			JniThreadAttachWrapper wrapper(m_native_activity);
			jmethodID mid = JavaTools::findJavaMethod(wrapper.getJNIEnv(),
					m_native_activity->clazz, "pauseSound", "()V");
			wrapper.getJNIEnv()->CallVoidMethod(m_native_activity->clazz, mid);
		}
	}

private:
	ANativeActivity * m_native_activity;
	bool m_valid;

};
