package com.example.jnidefensedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Fonctions JNI
    public native boolean isDebugDetected();
    public native String helloFromJNI();
    public native int factorial(int n);

    // Chargement de la bibliothèque native
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvStatus = findViewById(R.id.tvStatus);
        TextView tvHello = findViewById(R.id.tvHello);
        TextView tvFact = findViewById(R.id.tvFact);

        boolean suspicious = isDebugDetected();

        // Cas suspect
        if (suspicious) {

            tvStatus.setText("Etat securite : environnement suspect detecte");
            tvStatus.setTextColor(Color.RED);

            tvHello.setText("Fonctions natives desactivees");
            tvFact.setText("Calcul natif bloque");

        } else {

            // Cas normal
            tvStatus.setText("Etat securite : OK");
            tvStatus.setTextColor(Color.parseColor("#2E7D32"));

            tvHello.setText(helloFromJNI());

            int result = factorial(10);

            if (result >= 0) {
                tvFact.setText("Factoriel de 10 = " + result);
            } else {
                tvFact.setText("Erreur dans le calcul");
            }
        }
    }
}