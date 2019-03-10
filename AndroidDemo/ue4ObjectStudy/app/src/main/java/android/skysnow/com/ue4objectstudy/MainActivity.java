package android.skysnow.com.ue4objectstudy;

import android.skysnow.com.ue4objectstudy.JNIAPI.CoreObjectJNI;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(CoreObjectJNI.stringFromJNI());
    }

}
