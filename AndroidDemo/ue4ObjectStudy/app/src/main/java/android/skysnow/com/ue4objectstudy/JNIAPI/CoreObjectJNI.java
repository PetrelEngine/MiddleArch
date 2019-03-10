package android.skysnow.com.ue4objectstudy.JNIAPI;

/**
 * Created by liuqian8 on 2019/3/10.
 */

public class CoreObjectJNI
{
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("StudyCoreObjec");
    }

    public static native String stringFromJNI();
}
