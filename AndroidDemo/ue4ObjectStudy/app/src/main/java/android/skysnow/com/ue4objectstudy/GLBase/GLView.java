package android.skysnow.com.ue4objectstudy.GLBase;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

/**
 * Created by liuqian8 on 2019/4/16.
 */

public class GLView extends GLSurfaceView
{
    private BaseRenderer mBaseRenderer;
    public GLView(Context context) {
        this(context, (AttributeSet)null);
    }

    public GLView(Context context, AttributeSet attributeSet)
    {
        super(context, attributeSet);
        mBaseRenderer = new BaseRenderer(context);
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);
        setRenderer(mBaseRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
