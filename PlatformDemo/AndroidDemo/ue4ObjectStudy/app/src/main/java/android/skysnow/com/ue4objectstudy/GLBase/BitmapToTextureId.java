package android.skysnow.com.ue4objectstudy.GLBase;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.GLUtils;

import java.io.File;

/**
 * Created by liuqian8 on 2018/3/7.
 */

public class BitmapToTextureId
{
    private static Bitmap             mBitmap = null;
    private static BitmapToTextureId  mInstence;

    private BitmapToTextureId()
    {
    }

    public static BitmapToTextureId getInstence()
    {
        if(mInstence == null)
            mInstence = new BitmapToTextureId();
        return mInstence;
    }

    public int getTextureId(int resourceId,Context context)
    {
        return createTextureId(resourceId,context);
    }

    public int getTextureId(Bitmap bitmap)
    {
        return createTextureId(bitmap);
    }


    public int createTextureId(int width,int height)
    {
        int[] genTextureNames = new int[1];
        GLES20.glGenTextures(1, genTextureNames, 0);
        int textureId = genTextureNames[0];
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D,0,GLES20.GL_RGBA, width,height,0,GLES20.GL_RGBA,GLES20.GL_UNSIGNED_BYTE,null);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
        return textureId;
    }


    private int createTextureId(int resourceId, Context context)
    {
        BitmapFactory.Options bitmapScalingOptions = new BitmapFactory.Options();
        bitmapScalingOptions.inScaled = false;
        mBitmap = BitmapFactory.decodeResource(context.getResources(), resourceId, bitmapScalingOptions);

        int[] genTextureNames = new int[1];
        GLES20.glGenTextures(1, genTextureNames, 0);
        int textureId = genTextureNames[0];

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0/*, mBitmapFormat*/, mBitmap, 0);

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
        return textureId;
    }

    private int createTextureId(Bitmap bitmap)
    {
        int[] genTextureNames = new int[1];
        GLES20.glGenTextures(1, genTextureNames, 0);
        int textureId = genTextureNames[0];

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0/*, mBitmapFormat*/, bitmap, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
        return textureId;
    }

    public static int loadImgTexture(String filepath) {

        File file = new File(filepath);
        Bitmap bitmap = null;
        if (file.exists()) {
            bitmap = BitmapFactory.decodeFile(filepath);
        }

        int[] genTextureNames = new int[1];
        GLES20.glGenTextures(1, genTextureNames, 0);
        int textureId = genTextureNames[0];
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0/*, mBitmapFormat*/, bitmap, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

        if (bitmap != null) {
            bitmap.recycle();
        }
        if (file != null) {
            file = null;
        }
        return textureId;
    }
}
