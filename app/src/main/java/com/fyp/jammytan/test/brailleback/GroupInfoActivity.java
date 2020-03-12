package com.fyp.jammytan.test.brailleback;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.fyp.jammytan.test.R;

public class GroupInfoActivity extends Activity {
    private Button back;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.group_info);
    }
    public void onClickBackButton(View v) {
        finish();
    }
}
