package com.xiaomakj.hellogcc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TestJniMethods methods = new TestJniMethods();
        new MuchJNIShow().muchShow(19);
        //android.os.Debug.waitForDebugger();
        methods.test();
        setTitle(methods.nativeMethod());
        methods.newJniThreads(5);    //创建5个线程
//        Object obj = TestJniMethods.allocNativeBuffer(16L); //分配字节缓冲区
//        methods.freeNativeBuffer(obj);  //释放字节缓冲区
    }
}
