#include <jni.h>
#include <string>
#include <android/log.h>

#include <fcntl.h>             // 提供open()函数
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>            // 提供目录流操作函数
#include <string.h>
#include <sys/stat.h>        // 提供属性操作函数
#include <sys/types.h>         // 提供mode_t 类型
#include <stdlib.h>

#define TAG "jiqingke-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

extern "C" JNIEXPORT void JNICALL
Java_com_example_jnicmake_NDKTools_scanDir(
        JNIEnv *env,
        jclass jclass1,
        jstring dir1,
        jint depth
) {

    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    const char *path = env->GetStringUTFChars(dir1, 0);

    dir = opendir(path);
    if (dir == NULL) {
        LOGE("Open dir error...");
    } else {

        while ((ptr = readdir(dir)) != NULL) {
            if (strcmp(ptr->d_name, ".") == 0 ||
                strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
                continue;
            else if (ptr->d_type == 8) {   ///file

                if (strstr(ptr->d_name, ".rc")) {
                    //判断是不是txt文件
//                    LOGE("%s/%s\n", "文件", ptr->d_name);
                }
                LOGE("%s/%s\n", "文件", ptr->d_name);
            } else if (ptr->d_type == 10) {
                ///link file
//                LOGE("%s/%s\n", "link文件", ptr->d_name);
            } else if (ptr->d_type == 4) {   //dir
//                LOGE("%s/%s\n", "文件夹", ptr->d_name);
                memset(base, '\0', sizeof(base));
                strcpy(base, env->GetStringUTFChars(dir1, 0));
                strcat(base, "/");
                strcat(base, ptr->d_name);

                jstring childPath = env->NewStringUTF(base);
                Java_com_example_jnicmake_NDKTools_scanDir(env, jclass1, childPath, depth);
            }
        }
    }
    env->DeleteLocalRef(dir1);
    closedir(dir);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_jnicmake_NDKTools_getArray(
        JNIEnv *env,
        jclass jclass1
) {


}