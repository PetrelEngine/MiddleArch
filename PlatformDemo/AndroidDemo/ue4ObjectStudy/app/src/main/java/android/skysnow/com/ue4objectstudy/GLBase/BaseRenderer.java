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
        mApplicationSystemClassId = mCoreObjectJNI.InitialEngine(mContext.getAssets(),width,height);

        mCoreObjectJNI.RendererCreate(mApplicationSystemClassId,width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT|GLES30.GL_DEPTH_BUFFER_BIT);
        GLES30.glClearColor(0,0,0,0);
        mCoreObjectJNI.RendererFrame(mApplicationSystemClassId);
    }

    public void release()
    {
        mCoreObjectJNI.releaseEngine(mApplicationSystemClassId);
    }

    //触控回调方法
    public boolean onTouchEvent(MotionEvent e,CoreObjectJNI.applicationType type)
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
