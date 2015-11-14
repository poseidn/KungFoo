#pragma once

#include <DescentEngine/src/Log.h>
#include <string>
#include <jni.h>

class JavaTools {
public:
	static jmethodID findJavaMethod(JNIEnv * env, jobject obj, std::string const& name,
			std::string const& signature) {

		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, name.c_str(), signature.c_str());
		if (mid == 0) {
			logging::Fatal() << "Java Method " << name << " with signature " << signature << " not found";
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

class JavaInterface {
public:
	JavaInterface(JNIEnv * env, jobject libObject) :
			m_env(env), m_libObject(libObject), m_valid(true) {

	}

	bool isValid() const {
		return m_valid;
	}

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
	}

	int playSound(std::string const& soundName, float direction) {
		logging::DebugC<logging::Categories::Default>() << "Calling playSound in Java";
		jmethodID midPlaySound = JavaTools::findJavaMethod(m_env, m_libObject, "playSound",
				"(Ljava/lang/String;F)I");
		jstring theSoundname = JavaTools::toJavaString(m_env, soundName);
		int res = m_env->CallIntMethod(m_libObject, midPlaySound, theSoundname, direction);
		return res;
	}

	int playMusic(std::string const& musicName) {
		logging::DebugC<logging::Categories::Default>() << "Calling playMusic in Java";
		jmethodID midPlayMusic = JavaTools::findJavaMethod(m_env, m_libObject, "playMusic",
				"(Ljava/lang/String;)I");
		jstring theSoundname = JavaTools::toJavaString(m_env, musicName);
		int res = m_env->CallIntMethod(m_libObject, midPlayMusic, theSoundname);
		return res;
	}

	void stopPlay(int playId, float fadeOutTime) {
		logging::DebugC<logging::Categories::Default>() << "Calling stopPlay in Java";
		jmethodID midPlayMusic = JavaTools::findJavaMethod(m_env, m_libObject, "stopPlay", "(IF)V");
		m_env->CallVoidMethod(m_libObject, midPlayMusic, playId);
	}

	int loadImage(std::string const& imageName) {
		jmethodID midLoadImage = JavaTools::findJavaMethod(m_env, m_libObject, "loadImage",
				"(Ljava/lang/String;)I");
		jstring theImageName = JavaTools::toJavaString(m_env, imageName);
		int res = m_env->CallIntMethod(m_libObject, midLoadImage, theImageName);
		return res;
	}

private:
	JNIEnv * m_env;
	jobject m_libObject;
	bool m_valid;

};
