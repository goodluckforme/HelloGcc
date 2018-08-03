package com.xiaomakj.hellogcc;

/**
 * Created by Administrator on 2018/8/3.
 */

public class MuchJNIShow {
    public native void muchShow(int age);

    static {
        System.loadLibrary("TestJniMethodsTwo");
    }
}
