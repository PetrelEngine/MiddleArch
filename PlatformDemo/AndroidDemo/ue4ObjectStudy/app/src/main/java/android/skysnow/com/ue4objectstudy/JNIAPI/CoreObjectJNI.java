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


    //=================

    public long setAssetsManager(AssetManager ass)
    {
        return setAssetsManagerJNI(ass);
    }

    public void RendererCreate(long ApplicationSystemClassId,int width,int height)
    {
        RendererCreateJNI(ApplicationSystemClassId,width,height);
    }

    public void RendererFrame(long ApplicationSystemClassId)
    {
        RendererFrameJNI(ApplicationSystemClassId);
    }
    public void setTextureId(long ApplicationSystemClassId,String name,int texture2DId)
    {
        setTexture2DId(ApplicationSystemClassId,name,texture2DId);
    }

    public void  moveObj(long ApplicationSystemClassId)
    {
        move(ApplicationSystemClassId);
    }

    public void releaseEngine(long ApplicationSystemClassId)
    {
        engineRelease(ApplicationSystemClassId);
    }

    //=========================================================================================

    protected native long setAssetsManagerJNI(AssetManager ass);

    protected native void setTexture2DId(long ApplicationSystemClassId,String name,int texture2DId);

    protected native void RendererCreateJNI(long ApplicationSystemClassId,int width,int height);

    protected native void RendererFrameJNI(long ApplicationSystemClassId);

    protected native void move(long ApplicationSystemClassId);

    protected native void engineRelease(long ApplicationSystemClassId);
}
