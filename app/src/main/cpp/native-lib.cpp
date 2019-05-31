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
        jstring rootPath,
        jint depth
) {

//    DIR *dir;
//    struct dirent *ptr;
//    char base[1000];
//
//    const char *path = env->GetStringUTFChars(rootPath, 0);
//
//    dir = opendir(path);
//    if (dir == NULL) {
//        LOGE("Open dir error...");
//    } else {
//
//        while ((ptr = readdir(dir)) != NULL) {
//            if (strcmp(ptr->d_name, ".") == 0 ||
//                strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
//                continue;
//            else if (ptr->d_type == 8) {   ///file
//
//                if (strstr(ptr->d_name, ".rc")) {
//                    //判断是不是txt文件
////                    LOGE("%s/%s\n", "文件", ptr->d_name);
//                }
//                LOGE("%s/%s\n", "文件", ptr->d_name);
//            } else if (ptr->d_type == 10) {
//                ///link file
////                LOGE("%s/%s\n", "link文件", ptr->d_name);
//            } else if (ptr->d_type == 4) {   //dir
////                LOGE("%s/%s\n", "文件夹", ptr->d_name);
//                memset(base, '\0', sizeof(base));
//                strcpy(base, env->GetStringUTFChars(rootPath, 0));
//                strcat(base, "/");
//                strcat(base, ptr->d_name);
//
//                jstring childPath = env->NewStringUTF(base);
//                Java_com_example_jnicmake_NDKTools_scanDir(env, jclass1, childPath, depth);
//            }
//        }
//    }
//    env->DeleteLocalRef(rootPath);
//    closedir(dir);

    DIR *p_dir = NULL;
    struct dirent *p_entry = NULL;
    struct stat statbuf;

    p_dir = opendir(env->GetStringUTFChars(rootPath, 0));

    if (p_dir == NULL) {
        LOGE("打开文件失败");
        env->DeleteLocalRef(rootPath);
        return;
    }

    chdir(env->GetStringUTFChars(rootPath, 0));

    while (NULL != (p_entry = readdir(p_dir))) { // 获取下一级目录信息

        lstat(p_entry->d_name, &statbuf); // 获取下一级成员属性

        if (S_IFDIR & statbuf.st_mode) { // 判断下一级成员是否是目录  
            if (strcmp(".", p_entry->d_name) == 0 || strcmp("..", p_entry->d_name) == 0)
                continue;

//            LOGE("%*s%s/\n", depth, "目录", p_entry->d_name);
            Java_com_example_jnicmake_NDKTools_scanDir(env, jclass1,
                                                       env->NewStringUTF(p_entry->d_name),
                                                       depth + 4); // 扫描下一级目录的内容
        } else {
//            LOGE("%*s%s\n", depth, "文件", p_entry->d_name); // 输出属性不是目录的成员

            if (strstr(p_entry->d_name, ".avi")) {
//                    判断是不是txt文件
                LOGE("%s/%s\n", "文件", p_entry->d_name);

                jclass jcl_string=env->FindClass("java/lang/String");



            }
        }
    }
    chdir(".."); // 回到上级目录  
    env->DeleteLocalRef(rootPath);
    closedir(p_dir);
}