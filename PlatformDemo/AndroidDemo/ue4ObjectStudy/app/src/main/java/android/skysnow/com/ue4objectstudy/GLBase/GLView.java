package android.skysnow.com.ue4objectstudy.GLBase;

import android.content.Context;
import android.opengl.EGLExt;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

/**
 * Created by liuqian8 on 2019/4/16.
 */

public class GLView extends GLSurfaceView
{
    private BaseRenderer mBaseRenderer;

    private int mGLESMajorVersion;
    private int mEGLMajorVersion;
    private int mEGLMinorVersion;
    private volatile boolean sGLChecked =  false;
    public GLView(Context context) {
        this(context, (AttributeSet)null);
    }

    public GLView(Context context, AttributeSet attributeSet)
    {
        super(context, attributeSet);
        mBaseRenderer = new BaseRenderer(context);
        int glesMajorVersion = getGLESMajorVersion();

        if(glesMajorVersion<3){
            super.setEGLContextClientVersion(2);
        }else{
            super.setEGLContextClientVersion(3);
        }
        setPreserveEGLContextOnPause(true);
        setRenderer(mBaseRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

    public void release()
    {
        if(mBaseRenderer != null)
            mBaseRenderer.release();
    }

    @Override
    public boolean onTouchEvent(MotionEvent e)
    {
        return mBaseRenderer.onTouchEvent(e);
    }

    private   int getGLESMajorVersion(){
        if(!sGLChecked) checkGLVersion();
        return mGLESMajorVersion;
    }

    private void checkGLVersion() {
        // Get an EGL context and display
        final EGL10 egl = (EGL10) EGLContext.getEGL();
        final EGLDisplay display = egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);

        final int[] version = new int[2];
        if (!egl.eglInitialize(display, version))
            throw new IllegalStateException(
                    "Failed to initialize an EGL context while getting device capabilities.");
        mEGLMajorVersion = version[0];
        mEGLMinorVersion = version[1];
        // RajLog.d("Device EGL Version: " + version[0] + "." + version[1]);

        // Assume GLES 2 by default
        mGLESMajorVersion = 2;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2) {
            // The API for GLES3 might exist, we need to check
            // RajLog.d("Attempting to get an OpenGL ES 3 config.");

            // Find out how many EGLConfigs exist
            final int[] num_config = new int[1];
            egl.eglGetConfigs(display, null, 0, num_config);

            // Allocate and retrieve the EGLConfigs/handles
            int configCount = num_config[0];
            final EGLConfig[] configs = new EGLConfig[configCount];
            egl.eglGetConfigs(display, configs, configCount, num_config);

            // Check for a config that supports GLES 3 (using a manual search rather than
            // eglChooseConfig(), which may simply ignore the new ES3 bit on older versions)
            final int value[] = new int[1];
            for (EGLConfig config : configs) {
                egl.eglGetConfigAttrib(display, config, EGL10.EGL_RENDERABLE_TYPE, value);
                if ((value[0] & EGLExt.EGL_OPENGL_ES3_BIT_KHR) != 0) {
                    // TODO is this secondary check for color sizes useful?
                    // We have at least one GLES 3 config, can now use eglChooseConfig()
                    // to see if one of them has at least 4 bits per color
                    final int[] configAttribs = {
                            EGL10.EGL_RED_SIZE, 4, EGL10.EGL_GREEN_SIZE, 4, EGL10.EGL_BLUE_SIZE, 4,
                            EGL10.EGL_RENDERABLE_TYPE, EGLExt.EGL_OPENGL_ES3_BIT_KHR, EGL10.EGL_NONE};
                    value[0] = 0;
                    egl.eglChooseConfig(display, configAttribs, configs, 1, value);
                    mGLESMajorVersion = value[0] > 0 ? 3 : 2;
                    break;
                }
            }
        }
        egl.eglTerminate(display);
        Log.i("SkySnow","Determined GLES Major version to be:"+mGLESMajorVersion);
        sGLChecked = true;
    }

}
