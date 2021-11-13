package com.iot.miniprojectiot;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    String nilaiCahaya;
    String nilaiServo;

    TextView textView_ldr;
    TextView textView_servo;
    ToggleButton tbOn_Off;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView_ldr = findViewById(R.id.textView_nilaiLdr);
        textView_servo = findViewById(R.id.textView_nilaiServo);
        tbOn_Off = findViewById(R.id.tbOn_Off);

        DatabaseReference dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {

            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                nilaiCahaya = snapshot.child("/projectiot4/cahaya").getValue().toString();
                textView_ldr.setText(nilaiCahaya);

                nilaiServo = snapshot.child("/projectiot4/servo").getValue().toString();
                textView_servo.setText(nilaiServo);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }

        });

        tbOn_Off.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                DatabaseReference tombol = FirebaseDatabase.getInstance().getReference("/projectiot4/tombol");
                tombol.setValue(1);
            }else{
                DatabaseReference tombol = FirebaseDatabase.getInstance().getReference("/projectiot4/tombol");
                tombol.setValue(0);
            }
        });
    }
}