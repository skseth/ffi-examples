/*
These three pages were instrumental while trying to get this working.
I started with existing examples, got them working, and updated
them to make sure I undersood how things worked. If you are trying this
for the first time, I suggest adding a new method with different arguments
to the Java class and then calling it from this C program.
Use 'javap -s -p helloWorld.class' to get the new method signature.
After that is working, package the class in a jar file, update the class
path in this C source file, and get that working.
http://www.inonit.com/cygwin/jni/invocationApi/c.html
http://www.codeproject.com/Articles/22881/How-to-Call-Java-Functions-from-C-Using-JNI
http://java.sun.com/developer/onlineTraining/Programming/JDCBook/jniexamp.html
*/

#include <stdio.h>
#include <jni.h>

typedef void (*EncryptFn)(unsigned char*, int);
static EncryptFn externEncrypt;

static JNIEnv* env;
static jclass java_encrypt_class;
static jobject java_encrypt_instance;
static jmethodID java_encrypt_method;
static jmethodID java_main_method;

static void encrypt(JNIEnv*e, jobject o, jobject bb) {
    printf("  encrypt in cpp\n");
    if (externEncrypt != NULL) {
        unsigned char *iBuf = (unsigned char*) e->GetDirectBufferAddress(bb);
        long capacity = e->GetDirectBufferCapacity(bb);

        externEncrypt(iBuf, capacity);
    }
}

typedef int (*intFunc) ();

int bridge_int_func(intFunc f)
{
		return 42;
}

static JNINativeMethod methods[] = { 
    { (char *)"externEncrypt", (char *)"(Ljava/nio/ByteBuffer;)V", (void *)&encrypt },
};

void initialize_java_methods()
{
    jmethodID ctor;

    // register callback
    java_encrypt_class = env->FindClass("helloWorld");
    jint i = env->RegisterNatives(java_encrypt_class, methods, sizeof(methods)/sizeof(methods[0]));
    printf("  RegisterNatives\n");

    // Java Main Method
    java_main_method = env->GetStaticMethodID(java_encrypt_class, "main", "([Ljava/lang/String;)V");
    printf("  Initialized Main Method\n");
    
    // create instance
    ctor = env->GetMethodID(java_encrypt_class, "<init>", "()V");
    java_encrypt_instance = env->NewObject(java_encrypt_class, ctor);
    printf("  Created instance of java encrypt class\n");

    // call method
    java_encrypt_method = env->GetMethodID(java_encrypt_class, "encrypt", "()V");
    printf("  Initialized encrypt Method\n");
}


JNIEnv* initialize_vm(JavaVM **jvm)
{
    JavaVMInitArgs args;
    JavaVMOption options;
    args.version = JNI_VERSION_1_8;
    args.nOptions = 1;
    options.optionString = (char *)"-Djava.class.path=./";
    args.options = &options;
    args.ignoreUnrecognized = 0;
    int rv;
    rv = JNI_CreateJavaVM(jvm, (void**)&env, &args);
    if (rv < 0 || !env)
        printf("  Unable to Launch JVM %d\n",rv);
    else
        printf("  Launched JVM\n");
    return env;
}

int initialize_java() {
    printf("Initializing Java in CPP\n");
    JavaVM *jvm;
    env = initialize_vm(&jvm);
    if(env == NULL)
        return 1;
    initialize_java_methods();
    return 0;
}


extern "C" {
    int initialize_java_callback(EncryptFn e) {
        // initialize callback
        externEncrypt = e;

        // initialize JVM
        return initialize_java();
    }

    int invokeJavaEncrypt() {
        printf("  invoke encrypt in cpp");
        env->CallVoidMethod(java_encrypt_instance, java_encrypt_method, NULL);
    }

    int invokeJavaMain() {
        env->CallStaticVoidMethod(java_encrypt_class, java_main_method, NULL);        
    }
}
