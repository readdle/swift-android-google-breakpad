package com.readdle.crashsystem;

/**
 * Created by albert on 3/23/18.
 */
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.lang.ref.WeakReference;
import java.util.Date;
import java.util.UUID;

import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.DefaultHttpClient;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Build;
import android.util.Log;

import com.readdle.swiftjava.sample.BuildConfig;


public class NativeCrashManager {
    static final String TAG = "NativeCrashManager";


    private static class UploadDumpToHockeappAsyncTask extends AsyncTask<File,Void,Void>{
        private WeakReference<Context> contextRef;
        private final String hockeappIdentifier;

        UploadDumpToHockeappAsyncTask(Context context, String hockeappIdentifier){
            contextRef = new WeakReference<>(context);
            this.hockeappIdentifier = hockeappIdentifier;
        }


        @Override
        protected Void doInBackground(File... files) {
            Context context = contextRef.get();
            if(context != null){
                try {
                    File logfile = createLogFile(context);

                    for (File file : files) {
                        sendToBackend(file, logfile);
                        file.delete();
                    }
                    logfile.delete();
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
            return null;
        }

        public void sendToBackend(File dumpFile, File logFile){
            try {
                DefaultHttpClient httpClient = new DefaultHttpClient();
                HttpPost httpPost = new HttpPost("https://rink.hockeyapp.net/api/2/apps/" + this.hockeappIdentifier  + "/crashes/upload");

                MultipartEntity entity = new MultipartEntity();
                entity.addPart("attachment0", new FileBody(dumpFile));

                entity.addPart("log", new FileBody(logFile));
                httpPost.setEntity(entity);

                HttpResponse response = httpClient.execute(httpPost);

                Log.d(TAG, String.format("File %s was sent to hockeyapp, with status code %d", dumpFile.getAbsoluteFile(),response.getStatusLine().getStatusCode() ));
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }

        public static File createLogFile(Context context) {
            final Date now = new Date();

            try {
                // Create filename from a random uuid
                String filename = UUID.randomUUID().toString();

                File filepath = new File(NativeCrashManager.getDumpDir(context), filename + ".faketrace");
                Log.d(TAG, "Writing unhandled exception to: " + filepath.getAbsolutePath());

                // Write the stacktrace to disk
                BufferedWriter write = new BufferedWriter(new FileWriter(filepath));

                write.write("Package: " + context.getPackageName() + "\n");
                write.write("Version Code: " + BuildConfig.VERSION_CODE + "\n");
                write.write("Version Name: " +  BuildConfig.VERSION_NAME + "\n");
                write.write("Android: " + Build.VERSION.RELEASE + "\n");
                write.write("Manufacturer: " + Build.MANUFACTURER + "\n");
                write.write("Model: " + android.os.Build.MODEL + "\n");
                write.write("Date: " + now + "\n");
                write.write("\n");
                write.write("MinidumpContainer");
                write.flush();
                write.close();

                return filepath;
            }
            catch (Exception e) {
                e.printStackTrace();
            }

            return null;
        }
    }

    public static File getDumpDir(Context context){
        return context.getCacheDir();
    }

    /**
     * Sending dumps from dump directory to hockeyapp
     * Just walking in the dir and trying to find a .dmp file, if a file is found send it to hockeapp and DELETE it
     * @param context
     * @param identifier hockeyapp app identifier
     */
    public static void handleDumpFiles(Context context, String identifier) {
        File[] files = searchForDumpFiles(context);
        new UploadDumpToHockeappAsyncTask(context, identifier)
                .execute(files);
    }



    private static File[] searchForDumpFiles(Context context) {

        // Try to create the files folder if it doesn't exist
        File dir = NativeCrashManager.getDumpDir(context);
        boolean created = dir.mkdir();
        if (!created && !dir.exists()) {
            return new File[0];
        }

        // Filter for ".dmp" files
        FilenameFilter filter = new FilenameFilter() {
            public boolean accept(File dir, String name) {
                return name.endsWith(".dmp");
            }
        };
        String[] list = dir.list(filter);

        File[] result = new File[list.length];

        for (int i = 0; i < list.length; i++) {
            result[i] = new File(dir, list[i]);
        }
        return result;

    }
}