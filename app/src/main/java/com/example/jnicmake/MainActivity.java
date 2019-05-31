package com.example.jnicmake;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());

        final String path = Environment.getExternalStorageDirectory().getAbsolutePath();

        Log.e("jiqingke", "外部存储 = " + path);
        // USB目录 /storage/usb0/
        new Thread(new Runnable() {
            @Override
            public void run() {
                Log.e("jiqingke", "遍历开始");
                NDKTools.scanDir(path, 0);
            }
        }).start();
    }
}
