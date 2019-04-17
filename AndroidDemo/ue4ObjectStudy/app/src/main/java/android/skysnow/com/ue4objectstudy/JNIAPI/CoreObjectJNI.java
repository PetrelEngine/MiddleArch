package android.skysnow.com.ue4objectstudy.JNIAPI;

import android.content.res.AssetManager;

/**
 * Created by liuqian8 on 2019/3/10.
 */

public class CoreObjectJNI
{
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("StudyCoreObjec");
    }

    public CoreObjectJNI()
    {

    }

    public long setAssetsManager(AssetManager ass)
    {
        return setAssetsManagerJNI(ass);
    }

    public long RendererCreate(long RendererContextClassId,int width,int height)
    {
        return RendererCreateJNI(RendererContextClassId,width,height);
    }

    public void RendererFrame(long RendererContextClassId,long ApplicationSystemClassId)
    {
        RendererFrameJNI(RendererContextClassId,ApplicationSystemClassId);
    }

    //=========================================================================================

    protected native long setAssetsManagerJNI(AssetManager ass);

    protected native String stringFromJNI();

    protected native long RendererCreateJNI(long RendererContextClassId,int width,int height);

    protected native void RendererFrameJNI(long RendererContextClassId,long ApplicationSystemClassId);
}
