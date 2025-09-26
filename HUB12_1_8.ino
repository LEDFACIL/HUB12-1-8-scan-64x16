// P4.75 HUB12 1/8 scan 64x16 de un solo color, matrix control by Damián G. Lasso www.LASSO-TECH.com 09/2025

#define oe_pin     13 // OE en conector IDC HUB12
#define a_pin      12 // A en conector IDC HUB12
#define b_pin      14 // B en conector IDC HUB12
#define c_pin      33 // C en conector IDC HUB12
#define clk_pin    27 // S o CLK en conector IDC HUB12
#define sclk_pin   26 // L o SCLK o STB o LAT en conector IDC HUB12
#define dato_pinR  25 // R o Data en conector IDC HUB12

uint8_t mensaje[] = {0b11110111, 0b10000000, 0b11100011, 0b10000100, 0b11110011, 0b00000000, 0b11111111, 0b00000000, 0b00000110, 0b10001001, 0b00001001, 0b00001001, 0b10001001, 0b00000000, 0b11111111, 0b00000000, 0b10001001, 0b10001010, 0b10001010, 0b11111010, 0b10001010, 0b10001010, 0b10001010, 0b10001001, 0b11001111, 0b00101000, 0b00101000, 0b00101000, 0b00101000, 0b00101000, 0b00101000, 0b11001000, 0b01001010, 0b01001010, 0b01011011, 0b01101010, 0b01001001, 0b00000000, 0b11111111, 0b00000000,  0b01000100, 0b01000100, 0b11000111, 0b01000100, 0b10000111, 0b00000000, 0b11111111, 0b00000000, 0b10100010, 0b00100010, 0b00100010, 0b00111110, 0b00100010, 0b00100010, 0b00010100, 0b00001000, 0b00000111, 0b00000100, 0b00000100, 0b00000111, 0b00000100, 0b00000100, 0b00000100, 0b00000111, 0b00100100, 0b00101001, 0b00111001, 0b10100101, 0b00111001, 0b00000000, 0b11111111, 0b00000000, 0b11001111, 0b00101000, 0b00101110, 0b00101000, 0b00101111, 0b00000000, 0b11111111, 0b00000000, 0b10001110, 0b01010001, 0b01010001, 0b10010001, 0b01010001, 0b01010001, 0b01010001, 0b10001110,0b01111100, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01110010, 0b01001010, 0b01110011, 0b01001010, 0b01110001, 0b00000000, 0b11111111, 0b00000000, 0b01000111, 0b01000000, 0b11000000, 0b01000000, 0b10000000, 0b00000000, 0b11111111, 0b00000000, 0b11100111, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010111, 0b00001110, 0b10010001, 0b01010001, 0b01010001, 0b01010001, 0b01010001, 0b10010001, 0b00001110};

int fila = 0;
int bit = 0;

void setup() 
{  
  pinMode(oe_pin, OUTPUT);
  pinMode(a_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(c_pin, OUTPUT);
  pinMode(clk_pin, OUTPUT);
  pinMode(sclk_pin, OUTPUT);
  pinMode(dato_pinR, OUTPUT);  
  digitalWrite(oe_pin, 0);
  digitalWrite(a_pin, 0);
  digitalWrite(b_pin, 0);
  digitalWrite(c_pin, 0);
  digitalWrite(sclk_pin, 0);
  digitalWrite(clk_pin, 0);  
  digitalWrite(dato_pinR, 0);  
}

void loop() 
{
  digitalWrite(oe_pin, 0); // segundo movimiento de bit para habilitar/deshabilitar las salidas de los multiplexores, para evitar efecto "ghosting" generando un apagado forzado de todos los LEDs
  // Selectores de fila
  if(fila == 0) { digitalWrite(a_pin, 0); digitalWrite(b_pin, 0); digitalWrite(c_pin, 0); } // "fila == 0" corresponde a las filas 8 y 16 viendo a la matriz físicamente de frente contando desde arriba desde la 1 (primer fila) hacia abajo, la 16 (última de abajo).
  if(fila == 1) { digitalWrite(a_pin, 1); digitalWrite(b_pin, 1); digitalWrite(c_pin, 1); } // "fila == 1" corresponde a las filas 7 y 15
  if(fila == 2) { digitalWrite(a_pin, 0); digitalWrite(b_pin, 1); digitalWrite(c_pin, 1); } // "fila == 2" corresponde a las filas 6 y 14
  if(fila == 3) { digitalWrite(a_pin, 1); digitalWrite(b_pin, 0); digitalWrite(c_pin, 1); } // "fila == 3" corresponde a las filas 7 y 13
  if(fila == 4) { digitalWrite(a_pin, 0); digitalWrite(b_pin, 0); digitalWrite(c_pin, 1); } // "fila == 4" corresponde a las filas 4 y 12
  if(fila == 5) { digitalWrite(a_pin, 1); digitalWrite(b_pin, 1); digitalWrite(c_pin, 0); } // "fila == 5" corresponde a las filas 3 y 11
  if(fila == 6) { digitalWrite(a_pin, 0); digitalWrite(b_pin, 1); digitalWrite(c_pin, 0); } // "fila == 6" corresponde a las filas 2 y 10  
  if(fila == 7) { digitalWrite(a_pin, 1); digitalWrite(b_pin, 0); digitalWrite(c_pin, 0); } // "fila == 7" corresponde a las filas 1 y 9
  
  for(int i=0;i<=120;i+=8) // "for" para recorrer byte por byte del arreglo
  {     
    for(int x=7;x>=0;x--) // "for" para recorrer bit por bit del byte actual
    {
      bit = bitRead(mensaje[fila+i],x); // lectura del bit dentro del byte actual
      digitalWrite(dato_pinR, bit);     // escritura del bit en la salida 
      digitalWrite(clk_pin, 1);         // primer movimiento para consolidar el bit 
      digitalWrite(clk_pin, 0);         // segundo movimiento para consolidar el bit
    }    
  }

  digitalWrite(sclk_pin, 1); // primer movimiento para consolidar la salida de los 16 bytes de la fila actual
  digitalWrite(sclk_pin, 0); // segundo movimiento para consolidar la salida de los 16 bytes de la fila actual
  digitalWrite(oe_pin, 1); // primer movimiento de bit para habilitar/deshabilitar las salidas de los multiplexores, para evitar efecto "ghosting" generando un apagado forzado de todos los LEDs
  //delay(1); // estde delay genera una atenuación, es un detalle opcional

  fila++; // cambio de fila
  if(fila > 7) fila = 0;   
}
