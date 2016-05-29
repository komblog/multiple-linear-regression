// Linear regression calculator, written by Markus Bindhammer
// Online linear regression calculator:
// http://www.alcula.com/calculators/statistics/linear-regression/
// Program mencari nilai regresi linear berganda
// Edit by Heri J Situmorang
// https://github.com/komblog/
// silahkan baca readme terlebih dahulu

#include <dht.h>
dht DHT;

#define DHT11_PIN 2

int n = 0; 
float x1[20], x2[20];
float x1_2[20], x2_2[20];
float X1X2[20];
float y[20], y_2[20], X1Y[20], X2Y[20];

void setup() {
  Serial.begin(9600);
}

void loop() {
  float totalX1 = 0;
  float totalX2 = 0;
  float totalY = 0;
  float totalX1_2 = 0;
  float totalX2_2 = 0;
  float totalY_2 = 0;
  float totalX1X2 = 0;
  float totalX1Y = 0;
  float totalX2Y = 0;
  float tempX1 = 0;
  float tempX2 = 0;
  float tempY = 0;
  float tempX1_2 = 0;
  float tempX2_2 = 0;
  float tempY_2 = 0;
  float tempX1X2 = 0;
  float tempX1Y = 0;
  float tempX2Y = 0;
  Serial.println("masukkan suhu atau 'ESC'");
  char input_x1[20];
  get_input(input_x1, 20);
  
  if (strcmp (input_x1, "ESC") == 0 && n > 0) { //selesai atau belum
    int chk = DHT.read11(DHT11_PIN);
    for (int i = 0; i < n; i ++) {
      x1_2[i] = pow(x1[i],2); //mencari nilai x1^2
      x2_2[i] = pow(x2[i],2); //mencari nilai x2^2
      y_2[i] = pow(y[i],2); //mencari nilai y^2
      X1X2[i] = x1[i]*x2[i]; //mencari nilai x1*x2
      X1Y[i] = x1[i]*y[i]; //mencari nilai x1*y
      X2Y[i] = x2[i]*y[i]; //mencari nilai x2*y
    }
    for (int i = 0; i < n; i ++) {
      tempX1 = tempX1 + x1[i];
      tempX2 = tempX2 + x2[i];
      tempY = tempY + y[i];
      tempX1_2 = tempX1_2 + x1_2[i];
      tempX2_2 = tempX2_2 + x2_2[i];
      tempY_2 = tempY_2 + y_2[i];
      tempX1X2 = tempX1X2 + X1X2[i];
      tempX1Y = tempX1Y + X1Y[i];
      tempX2Y = tempX2Y + X2Y[i]; 
    }
    
    totalX1 = totalX1 + tempX1; //mencari nilai sigma x1
    totalX2 = totalX2 + tempX2; //mencari nilai sigma x2  
    totalY = totalY + tempY; //mencari nilai sigma y
    totalX1_2 = totalX1_2 + tempX1_2; //mencari sigma x1^2
    totalX2_2 = totalX2_2 + tempX2_2; //mencari sigma x2^2
    totalY_2 = totalY_2 + tempY_2; //mencari sigma y^2
    totalX1X2 = totalX1X2 + tempX1X2; //mencari sigma X1*X2
    totalX1Y = totalX1Y + tempX1Y; //mencari sigma x1*y
    totalX2Y = totalX2Y + tempX2Y; //mencari sigma x2*y

    float C = totalX1_2 - (pow(totalX1,2)/n);
    float D = totalX2_2 - (pow(totalX2,2)/n);
    float E = totalY_2 - (pow(totalY,2)/n);
    float F = totalX1Y - ((totalX1 * totalY)/n);
    float G = totalX2Y - ((totalX2 * totalY)/n);
    float H = totalX1X2 - ((totalX1 * totalX2)/n);

    
    float b1 = ((D*F)-(G*H))/((C*D)-(pow(H,2))); //mencari nilai b1
    float b2 = ((C*G)-(F*H))/((C*D)-(pow(H,2))); //mencari nilai b2
    float a = ((totalY) - (b1*totalX1) - (b2*totalX2))/n; //mencari nilai a
    int humid = DHT.humidity;
    int temp = DHT.temperature;

    
    float hasil = a + (b1*temp) + (b2*humid); //mencari nilai Y
    Serial.print("SigmaX1X2 = ");
    Serial.println(totalX1X2);
    Serial.print("SigmaX1 = ");
    Serial.println(totalX1);
    Serial.print("SigmaX2 = ");
    Serial.println(totalX2);
    Serial.print("C = ");
    Serial.println(C);
    Serial.print("D = ");
    Serial.println(D);
    Serial.print("E = ");
    Serial.println(E);
    Serial.print("F = ");
    Serial.println(F);
    Serial.print("G = ");
    Serial.println(G);
    Serial.print("H = ");
    Serial.println(H);
    
    Serial.println("# Rumus Persamaan Regresi Linier Berganda #");
    Serial.print("# Y = ");
    Serial.print(a,4);
    Serial.print(" + ");
    Serial.print(b1,4);
    Serial.print("X1");
    Serial.print(" + ");
    Serial.print(b2,4);
    Serial.println("X2    #");
    Serial.print("# Suhu = ");
    Serial.println(temp);
    Serial.print("# Kelembaban = ");
    Serial.println(humid);
    Serial.print("Y = ");
    Serial.println(hasil, 4);
    Serial.println("# ----------------------------------------#");
  } 
  else {
    int x1_value = atoi(input_x1);
    x1[n] = x1_value;
    Serial.print("suhu_");
    Serial.print(n + 1);
    Serial.print(" = ");
    Serial.println(x1_value);
    Serial.println("");
    Serial.println("masukkan kelembaban");
    char input_x2[20];
    get_input(input_x2, 20);
    int x2_value = atoi(input_x2);
    x2[n] = x2_value;
    Serial.print("kelembaban_");
    Serial.print(n + 1);
    Serial.print(" = ");
    Serial.println(x2_value);
    Serial.println("");
    Serial.println("masukkan y");
    char input_y[20];
    get_input(input_y, 20);
    float y_value = atoi(input_y);
    y[n] = y_value;
    Serial.print("y_");
    Serial.print(n + 1);
    Serial.print(" = ");
    Serial.println(y_value);
    Serial.println("");
    n ++; 
  }
}

void get_input(char pd[], int pd_size) {
  while (Serial.available() == 0){
  }
    String inputBuffer;
    while (Serial.available() > 0) {
      char ch = Serial.read();
      inputBuffer += ch; 
      delay (10);
    }
    if (inputBuffer.length() > 0) { 
      inputBuffer.toCharArray(pd, pd_size); 
    }  
}
        
