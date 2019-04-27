package android.skysnow.com.ue4objectstudy;

import android.skysnow.com.ue4objectstudy.GLBase.GLView;
import android.skysnow.com.ue4objectstudy.JNIAPI.CoreObjectJNI;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private GLView mGLView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
        // Example of a call to a native method
//        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(CoreObjectJNI.stringFromJNI());
        mGLView =  new GLView(this);
        setContentView(mGLView);
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
    protected void onDestroy(){
        super.onDestroy();
    }
}
