// Pines de los LEDs
const int pinLedGreen = 2;
const int pinLedYellow = 3;
const int pinLedRed = 4;

// Pin del botón
const int buttonPin = 9; // ESP32 conectado al pin del botón


int estadoDelBoton;  // Estado actual del botón

void setup() {
  Serial.begin(9600);                // Inicializar serial
  pinMode(buttonPin, INPUT_PULLUP);   // Configurar pin del botón en modo pull-up
  pinMode(pinLedGreen, OUTPUT);
  digitalWrite(pinLedGreen, HIGH);    // Mantener el LED verde encendido por defecto

  pinMode(pinLedYellow, OUTPUT);
  digitalWrite(pinLedYellow, LOW);

  pinMode(pinLedRed, OUTPUT);
  digitalWrite(pinLedRed, LOW);
}

void loop() {
  // Leer el estado actual del botón
  estadoDelBoton = digitalRead(buttonPin);

  // Si el botón está presionado (LOW)
  if (estadoDelBoton == LOW) {
    Serial.println("Botón presionado, ejecutando la secuencia del semáforo...");

    // Hacer parpadear el LED verde 3 veces
    for (int i = 0; i < 3; i++) {
      digitalWrite(pinLedGreen, HIGH); // Encender verde
      delay(300);                      // Pausa de 300 ms
      digitalWrite(pinLedGreen, LOW);  // Apagar verde
      delay(300);                      // Pausa de 300 ms
    }

    // Cambiar al LED amarillo
    digitalWrite(pinLedGreen, LOW);
    digitalWrite(pinLedYellow, HIGH);
    delay(1000);                       // Esperar 1 segundos en amarillo

    // Cambiar al LED rojo y mantenerlo encendido mientras el botón esté presionado
    digitalWrite(pinLedYellow, LOW);
    digitalWrite(pinLedRed, HIGH);

    // Mantenerse en rojo mientras el botón siga presionado
    while (digitalRead(buttonPin) == LOW) {
      // Aquí el semáforo se mantiene en rojo hasta que el botón sea liberado
      delay(100);
    }

    // Cuando el botón es liberado, apagar el LED rojo y volver al verde
    digitalWrite(pinLedRed, LOW);
  }

  // Siempre mantener el LED verde encendido si el botón no está presionado
  digitalWrite(pinLedGreen, HIGH);
}
