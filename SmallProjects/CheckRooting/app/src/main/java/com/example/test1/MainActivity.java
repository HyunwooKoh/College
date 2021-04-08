package com.example.test1;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.BatteryManager;
import android.os.Build;
import android.telephony.TelephonyManager;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.util.List;

import static android.content.Context.TELEPHONY_SERVICE;

public class MainActivity extends AppCompatActivity {

    private String[] binaryPaths = {
            "/data/local/",
            "/data/local/bin/",
            "/data/local/xbin/",
            "/sbin/",
            "/su/bin/",
            "/system/bin/",
            "/system/bin/.ext/",
            "/system/bin/failsafe/",
            "/system/sd/xbin/",
            "/system/usr/we-need-root/",
            "/system/xbin/",
            "/system/app/Superuser.apk",
            "/cache",
            "/data",
            "/dev"
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        View.OnClickListener em_dtct_listener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TextView eTextView;
                String em_res = " ";

                eTextView = (TextView) findViewById(R.id.em_detect_result1);
                em_res = String.valueOf(nw_op_detect());
                eTextView.setText(em_res);

                eTextView = (TextView) findViewById(R.id.em_detect_result2);
                em_res = String.valueOf(os_build_detect());
                eTextView.setText(em_res);

                /*
                eTextView = (TextView) findViewById(R.id.em_detect_result2);
                em_res = String.valueOf(os_build_detect());
                eTextView.setText(em_res);
                */

                eTextView = (TextView) findViewById(R.id.em_detect_result3);
                em_res = String.valueOf(pkg_manager_detect());
                eTextView.setText(em_res);


                eTextView = (TextView)findViewById(R.id.em_detect_result4);
                //em_res = String.valueOf(os_build_detect());
                em_res = String.valueOf(proc_chk_detect());
                eTextView.setText(em_res);


                /*
                eTextView = (TextView) findViewById(R.id.em_detect_result4);
                em_res = "FINGERPRINT:" + Build.FINGERPRINT + "\n" +
                        "MODEL:" + Build.MODEL + "\n" +
                        "DEVICE:" + Build.DEVICE + "\n" +
                        "BOARD:" + Build.BOARD + "\n" +
                        "HOST:" + Build.HOST + "\n" +
                        "PRODUCT:" + Build.PRODUCT + "\n" +
                        "HARDWARE:" + Build.HARDWARE + "\n" +
                        "ID:" + Build.ID + "\n"+
                        "BOOTLOADER:"+Build.BOOTLOADER+"\n"+
                        "SERIAL:"+ Build.SERIAL+"\n"+
                        "USER:"+Build.USER+"\n";
                eTextView.setText(em_res);*/


            }
        };

        Button bt_em_dtct = (Button) findViewById(R.id.button3);
        bt_em_dtct.setOnClickListener(em_dtct_listener);

    }

    //Emulator Detect By Network Operator
    public boolean nw_op_detect() {
        TelephonyManager tm = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
        String nw_op = tm.getNetworkOperatorName();

        if ("Android".equals(nw_op)) {
            return true;
        } else {
            return false;
        }
    }

    //Name Of Network Operator
    public String n_opname() {
        TelephonyManager tm = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
        String nw_op = tm.getNetworkOperatorName();
        return nw_op;
    }

    //Emulator Detect By System Property
    public boolean sys_prop_detect() {
        String prop = System.getProperty("os.arch");
        if (prop.equals("i686")) {
            return true;
        } else {
            return false;
        }
    }

    //Emulator Detect By OS Build
    public boolean os_build_detect() {
        if (Build.PRODUCT.contains("emulator")) {
            return true;
        }
        else if (Build.PRODUCT.contains("simulator")) {
            return true;
        }
        else if (Build.FINGERPRINT.contains("x86")) {
            return true;
        }
        else if(Build.HARDWARE.contains("android_x86")){
            return true;
        }
        else {
            return false;
        }
    }

    //Emulator Detect By Package Manager (Especially NFC)
    public boolean pkg_manager_detect() {
        PackageManager pm = (PackageManager)getPackageManager();
        boolean rtn = pm.hasSystemFeature(PackageManager.FEATURE_NFC);
        rtn = !rtn;
        return rtn;
    }

    //Emulator Detect By Running Process
    public boolean proc_chk_detect(){
        String proc="";
        ActivityManager am = (ActivityManager)getSystemService(ACTIVITY_SERVICE);
        List<ActivityManager.RunningAppProcessInfo> plist=am.getRunningAppProcesses();

        for(int i = 0; i < plist.size(); i++) {
            proc+=(plist.get(i).processName+"\n");
        }

        if(proc.contains("android.emu")){
            return true;
        }
        else{
            return false;
        }

    }



    public void OnbuttonClick(View view) {
        if(view.getId() == R.id.button) {

            TextView mTextView;
            String result = "";

            mTextView  = view.findViewById(R.id.file_detecting_result);
            result = String.valueOf(Su_File_detecting());
            mTextView.setText(result);

            mTextView  = view.findViewById(R.id.su_command_result);
            result = String.valueOf(su_command());
            mTextView.setText(result);

            mTextView  = view.findViewById(R.id.package_search_result);
            result = String.valueOf(pakage_search());
            mTextView.setText(result);

            mTextView  = view.findViewById(R.id.build_tag_result);
            result = String.valueOf(find_build_tag());
            mTextView.setText(result);

        }
    }

    private boolean Su_File_detecting() {
        String filename = "su";
        for (String path : binaryPaths) {
            File f = new File(path, filename);
            boolean fileExists = f.exists();
            if (fileExists) {
                return true;
            }
        }
        return false;
    }

    private boolean su_command() {
        try {
            Runtime.getRuntime().exec("su");

        } catch ( Exception e) {
            //Exception이 발생한다면 Rooting이 되지 않은 것으로 확인
            return false;
        }
        return true;
    }

    private boolean pakage_search() {
        String filename = "busybox";
        for (String path : binaryPaths) {
            File f = new File(path, filename);
            boolean fileExists = f.exists();
            if (fileExists) {
                return true;
            }
        }
        return false;
    }

    private boolean find_build_tag() {
        String buildTags = android.os.Build.TAGS;
        return buildTags != null && buildTags.contains("test-keys");
    }



}
