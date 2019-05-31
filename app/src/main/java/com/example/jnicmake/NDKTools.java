package com.example.jnicmake;

import java.util.ArrayList;

public class NDKTools {
    static {
        System.loadLibrary("native-lib");
    }

    public static native void scanDir(String dir, int depth);
}
