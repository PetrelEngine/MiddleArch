package android.skysnow.com.ue4objectstudy;
import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.skysnow.com.ue4objectstudy.GLBase.GLView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends Activity {
    private GLView mGLView;
    private String mAssetsPath = "SkySnowResources";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        copyAssetsDir2Phone(mAssetsPath);
        mGLView = (GLView) findViewById(R.id.gl_view);
//        setContentView(mGLView);
    }


    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mGLView.release();
    }

    public void copyAssetsDir2Phone(String filePath) {
        try {
            String[] fileList = getAssets().list(filePath);
            if (fileList.length > 0) {//如果是目录
                File file = new File(getFilesDir().getAbsolutePath() + File.separator + filePath);
                file.mkdirs();//如果文件夹不存在，则递归
                for (String fileName : fileList) {
                    filePath = filePath + File.separator + fileName;

                    copyAssetsDir2Phone(filePath);

                    filePath = filePath.substring(0, filePath.lastIndexOf(File.separator));
//                    Log.e("oldPath", filePath);
                }
            } else {//如果是文件
                InputStream inputStream = getAssets().open(filePath);
                //getFilesDir() 获得当前APP的安装路径 /data/data/包名/files 目录
                File file = new File(Environment.getExternalStorageDirectory() + File.separator + filePath);
                Log.i("SkySnow:", "file:" + file);
                if (!file.exists() || file.length() == 0) { // 文件不存在
                    File parent = file.getParentFile();
                    if (parent != null && !file.exists()) {
                        parent.mkdirs();
                    }
                    FileOutputStream fos = new FileOutputStream(file);
                    int len = -1;
                    byte[] buffer = new byte[1024];
                    while ((len = inputStream.read(buffer)) != -1) {
                        fos.write(buffer, 0, len);
                    }
                    fos.flush();
                    inputStream.close();
                    fos.close();
                    showToast("文件夹数据复制完毕");
                } else {
                    showToast("文件夹数据已存在，无需复制");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

}
