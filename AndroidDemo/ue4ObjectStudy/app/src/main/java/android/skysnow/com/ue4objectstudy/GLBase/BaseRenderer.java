package android.skysnow.com.ue4objectstudy.GLBase;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.skysnow.com.ue4objectstudy.JNIAPI.CoreObjectJNI;
import android.skysnow.com.ue4objectstudy.R;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by liuqian8 on 2019/4/16.
 */

public class BaseRenderer implements GLSurfaceView.Renderer
{
    private Context mContext;
    private CoreObjectJNI mCoreObjectJNI;
    private long mRendererContextClassId;
    private long mApplicationSystemClassId;
    public BaseRenderer(Context context)
    {
        mContext = context;
        mCoreObjectJNI = new CoreObjectJNI();
    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        mRendererContextClassId = mCoreObjectJNI.setAssetsManager(mContext.getAssets());
        mApplicationSystemClassId = mCoreObjectJNI.RendererCreate(mRendererContextClassId,width,height);
        int fishID = BitmapToTextureId.getInstence().getTextureId(R.drawable.fish,mContext);
        Log.i("SkySnow:", "onSurfaceChanged: "+fishID);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"fish",fishID);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT|GLES20.GL_DEPTH_BUFFER_BIT);
        GLES20.glClearColor(0,0,0,0);
        mCoreObjectJNI.RendererFrame(mRendererContextClassId,mApplicationSystemClassId);
    }
}
