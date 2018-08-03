package com.xiaomakj.hellogcc;

public class TestJniMethods {
    public native void test();

    public native String nativeMethod();

    public native void newJniThreads(int i);

    public native Object allocNativeBuffer(long size);

    public native void freeNativeBuffer(Object obj);

    static {
        System.loadLibrary("TestJniMethodsOne");
    }
}
