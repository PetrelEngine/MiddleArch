package android.skysnow.com.ue4objectstudy.GLBase;

import android.content.Context;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.skysnow.com.ue4objectstudy.JNIAPI.CoreObjectJNI;
import android.skysnow.com.ue4objectstudy.R;
import android.util.Log;
import android.view.MotionEvent;

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
        int fishID = BitmapToTextureId.getInstence().getTextureId(R.drawable.fish,mContext);
        Log.i("SkySnow:", "onSurfaceChanged: "+fishID);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"fish",fishID);

        int box_diffuse = BitmapToTextureId.getInstence().getTextureId(R.drawable.toyboxdiffuse,mContext);
        int box_disp = BitmapToTextureId.getInstence().getTextureId(R.drawable.toyboxdisp,mContext);
        int box_normal = BitmapToTextureId.getInstence().getTextureId(R.drawable.toyboxnormal,mContext);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"box_diffuse",box_diffuse);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"box_disp",box_disp);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"box_normal",box_normal);

        int bri_diffuse = BitmapToTextureId.getInstence().getTextureId(R.drawable.bricks2,mContext);
        int bri_disp = BitmapToTextureId.getInstence().getTextureId(R.drawable.bricks2_disp,mContext);
        int bri_normal = BitmapToTextureId.getInstence().getTextureId(R.drawable.bricks2_normal,mContext);

        mCoreObjectJNI.setTextureId(mRendererContextClassId,"bri_diffuse",bri_diffuse);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"bri_disp",bri_disp);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"bri_normal",bri_normal);

        int GammaTextureId = BitmapToTextureId.getInstence().getTextureId(R.drawable.wood,mContext);
        mCoreObjectJNI.setTextureId(mRendererContextClassId,"gamma",GammaTextureId);

        mApplicationSystemClassId = mCoreObjectJNI.RendererCreate(mRendererContextClassId,width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT|GLES30.GL_DEPTH_BUFFER_BIT);
        GLES30.glClearColor(0,0,0,0);
        mCoreObjectJNI.RendererFrame(mRendererContextClassId,mApplicationSystemClassId);
    }

    //触控回调方法
    public boolean onTouchEvent(MotionEvent e)
    {

        switch (e.getAction())
        {
            case MotionEvent.ACTION_DOWN:

                break;
            case MotionEvent.ACTION_MOVE:
                if(mCoreObjectJNI != null)
                    mCoreObjectJNI.moveObj(mApplicationSystemClassId);
                break;
            case MotionEvent.ACTION_UP:
                break;
        }
        return true;
    }
}
