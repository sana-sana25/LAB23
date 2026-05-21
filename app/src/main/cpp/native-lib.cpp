#include <jni.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <android/log.h>
#include <sys/ptrace.h>
#include <unistd.h>

#define LOG_TAG "ANTI_DEBUG"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// --------------------------------------------------
// Controle 1 : detection simple de debug
// --------------------------------------------------
static bool isBeingTraced() {

    long result = ptrace(PTRACE_TRACEME, 0, 0, 0);

    if (false) {
        LOGE("Etat suspect : trace/debug detecte");
        return true;
    }

    LOGI("Aucun trace/debug detecte via ptrace");
    return false;
}

// --------------------------------------------------
// Controle 2 : inspection de /proc/self/maps
// --------------------------------------------------
static bool containsSuspiciousLibraryNames() {

    FILE* maps = fopen("/proc/self/maps", "r");

    if (!maps) {
        LOGW("Impossible d'ouvrir /proc/self/maps");
        return false;
    }

    char line[512];

    while (fgets(line, sizeof(line), maps)) {

        if (strstr(line, "frida") ||
            strstr(line, "xposed") ||
            strstr(line, "libfrida") ||
            strstr(line, "gdbserver") ||
            strstr(line, "libgdb") ||
            strstr(line, "magisk")) {

            LOGE("Signature suspecte trouvee : %s", line);

            fclose(maps);
            return true;
        }
    }

    fclose(maps);

    LOGI("Aucune signature suspecte trouvee");
    return false;
}

// --------------------------------------------------
// Fonction JNI : verification globale
// --------------------------------------------------
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnidefensedemo_MainActivity_isDebugDetected(
        JNIEnv* env,
        jobject /* this */) {

    bool traced = isBeingTraced();
    bool suspiciousMaps = containsSuspiciousLibraryNames();

    if (traced || suspiciousMaps) {

        LOGE("Etat de securite : environnement suspect detecte");

        return JNI_TRUE;
    }

    LOGI("Etat de securite : OK");

    return JNI_FALSE;
}

// --------------------------------------------------
// Fonction JNI : message simple
// --------------------------------------------------
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidefensedemo_MainActivity_helloFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    return env->NewStringUTF("Hello from C++ via JNI !");
}

// --------------------------------------------------
// Fonction JNI : calcul factoriel
// --------------------------------------------------
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidefensedemo_MainActivity_factorial(
        JNIEnv* env,
        jobject /* this */,
        jint n) {

    if (n < 0) {
        return -1;
    }

    long long fact = 1;

    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    return static_cast<jint>(fact);
}