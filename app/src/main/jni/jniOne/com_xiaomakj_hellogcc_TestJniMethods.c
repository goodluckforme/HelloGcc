/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_xiaomakj_hellogcc_TestJniMethods */
#include <string.h>
#include <android/log.h>
#include <pthread.h>
#include "com_xiaomakj_hellogcc_TestJniMethods.h"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "com.droider.jnimethods", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "com.droider.jnimethods", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "com.droider.jnimethods", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "com.droider.jnimethods", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "com.droider.jnimethods", __VA_ARGS__)

JNIEnv *g_env;
JavaVM *g_vm;	//下面多线程程序用到
pthread_mutex_t thread_mutex;
jclass native_class;

#ifndef NELEM //计算结构元素个数
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

/*
 * Class:     com_xiaomakj_hellogcc_TestJniMethods
 * Method:    nativeMethod
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xiaomakj_hellogcc_TestJniMethods_nativeMethod
  (JNIEnv * env , jobject object){
     const char * chs = "你好!NativeMethod";
  	 return (*env)->NewStringUTF(env, chs);
  }
/*
 * Class:     com_xiaomakj_hellogcc_TestJniMethods
 * Method:    test
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiaomakj_hellogcc_TestJniMethods_test
  (JNIEnv * env, jclass clazz){

    jintArray int_array = (*env)->NewIntArray(env, 5); 	//创建int数组
    	LOGV("NewIntArray() --> %d", (*env)->GetArrayLength(env, int_array)); //获取数组长度
    	const jint ints[] = {11, 12, 13, 14, 15};
    	(*env)->SetIntArrayRegion(env, int_array, 0, 5, ints); //设置数组一个范围的值ֵ
    	LOGV("SetIntArrayRegion() --> %d,%d,%d,%d,%d",
    			ints[0], ints[1], ints[2], ints[3], ints[4]);
    	jint ints2[2] = {0, 0};
    	(*env)->GetIntArrayRegion(env, int_array, 1, 2, ints2); //获取数组一个范围的值
    	LOGV("GetIntArrayRegion() --> %d,%d", ints2[0], ints2[1]);
    	jint* array_ints = (*env)->GetIntArrayElements(env, int_array, NULL); //获取指向所有元素的指针
    	LOGV("GetIntArrayElements() --> %d,%d,%d,%d,%d",
    			array_ints[0], array_ints[1], array_ints[2], array_ints[3], array_ints[4]);
    	(*env)->ReleaseIntArrayElements(env, int_array, array_ints, 0); //释放指向所有元素的指针
    	LOGV("ReleaseIntArrayElements()");

  }

/*
 * Class:     com_xiaomakj_hellogcc_TestJniMethods
 * Method:    allocNativeBuffer
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_xiaomakj_hellogcc_TestJniMethods_allocNativeBuffer
(JNIEnv* env, jobject obj, jlong size){
    void* buffer = malloc(size);
	jobject directBuffer = (*env)->NewDirectByteBuffer(env, buffer, size);
	LOGV("NewDirectByteBuffer() --> %d", (int)size);
	return directBuffer;
}


void *thread_func(void *arg){
	JNIEnv *env;
	pthread_mutex_lock(&thread_mutex);
	if (JNI_OK != (*g_vm)->AttachCurrentThread(g_vm, &env, NULL)){
		LOGE("AttachCurrentThread() failed");
		return NULL;
	}
	LOGV("AttachCurrentThread() --> thread:%d", (jint)arg);
	(*g_vm)->DetachCurrentThread(g_vm);
	LOGV("DetachCurrentThread() --> thread:%d", (jint)arg);
	pthread_mutex_unlock(&thread_mutex);
	pthread_exit(0);
	return NULL;
}

JNIEXPORT void newJniThreads(JNIEnv* env, jobject obj, jint nums){
	(*env)->GetJavaVM(env, &g_vm);	//保存全局JavaVM
	LOGV("GetJavaVM()");
	pthread_t* pt = (pthread_t*)malloc(sizeof(pthread_t)* nums);
	pthread_mutex_init(&thread_mutex, NULL);
	int i;
	for (i = 0 ; i < nums; i++){
		pthread_create(&pt[i], NULL, &thread_func, (void*)i); //创建线程
	}
	free(pt);
}

static JNINativeMethod methods[] = {
	{"newJniThreads", "(I)V", (void*)newJniThreads}
};

jint JNI_OnLoad(JavaVM* vm, void* reserved){
	if(JNI_OK != (*vm)->GetEnv(vm, (void**)&g_env, JNI_VERSION_1_6)){ //加载指定版本的JNI
		return -1;
	}
	LOGV("JNI_OnLoad()");
	native_class = (*g_env)->FindClass(g_env, "com/xiaomakj/hellogcc/TestJniMethods");
	if (JNI_OK ==(*g_env)->RegisterNatives(g_env, 	//注册未声明的本地方法
			native_class, methods, NELEM(methods))){
		LOGV("RegisterNatives() --> nativeMethod() ok");
	} else {
		LOGE("RegisterNatives() --> nativeMethod() failed");
		return -1;
	}
	return JNI_VERSION_1_6;
}

void JNI_OnUnLoad(JavaVM* vm, void* reserved){
	LOGV("JNI_OnUnLoad()");
	(*g_env)->UnregisterNatives(g_env, native_class);
	LOGV("UnregisterNatives()");
}
