int const MINI_PAUSA_MILLISECONDI = 1000;
int const MAXI_PAUSA_MILLISECONDI = 5 * MINI_PAUSA_MILLISECONDI;

class ArduinoComponente {
  protected:
  	int pinNumber;
  	static int lastPinNumber; 
  public:
  	ArduinoComponente() { 
      pinNumber = lastPinNumber++; 
      pinMode(pinNumber, OUTPUT);
    };
  	void accendi() { digitalWrite(pinNumber, HIGH); };
  	void spegni () { digitalWrite(pinNumber, LOW ); };
   	// ArduinoComponente(int x) : pinNumber(x) {
    //  pinMode(pinNumber, OUTPUT);
    //  lastPinNumber = x;
    // };
};

class Vibratore : public ArduinoComponente {};
class Led 		  : public ArduinoComponente {};

class CassaSuono : public ArduinoComponente {
  private:
    int static const  FREQUENZA_SUONO                 = 440;
    int        const  NUMERO_VOLTE_RIPETIZIONE_SUONO  = 10;
    int        const  DURATA_SUONO_MILLISECONDI       = MINI_PAUSA_MILLISECONDI / NUMERO_VOLTE_RIPETIZIONE_SUONO;
  public:
  	void suona(int parametroFrequenzaSuono = FREQUENZA_SUONO) {
  		tone(pinNumber, parametroFrequenzaSuono, DURATA_SUONO_MILLISECONDI);
  	};
    void suonaLoop() {
      for(int i=1; i<=NUMERO_VOLTE_RIPETIZIONE_SUONO; i++) {
      	suona();
        if(i!=NUMERO_VOLTE_RIPETIZIONE_SUONO) {
          delay(DURATA_SUONO_MILLISECONDI*3);
        };
      };
    };
};

class Semaforo {
  private:
    Led luceVerde, luceGiallo, luceRosso;
  
  public:
  	void passa() {
      luceVerde  .accendi();
      luceGiallo .spegni ();
      luceRosso  .spegni ();
  	};
  	void attenzione() {
      luceVerde  .spegni ();
      luceGiallo .accendi();
      luceRosso  .spegni ();
  	};
    void stop() {
      luceVerde  .spegni ();
      luceGiallo .spegni ();
      luceRosso  .accendi();
  	};
};

int ArduinoComponente::lastPinNumber = 2;

Semaforo   semaforoMacchine, semaforoPedoni;
CassaSuono cassaPedoni;
Vibratore  vibratorePedoni;

void loop() {
  semaforoMacchine.passa();
  semaforoPedoni.stop();
  
  delay(MAXI_PAUSA_MILLISECONDI);
  
  semaforoMacchine.attenzione();
  semaforoPedoni.stop();
  
  delay(MINI_PAUSA_MILLISECONDI);
  
  semaforoMacchine.stop();
  semaforoPedoni.passa();
  
  delay(MAXI_PAUSA_MILLISECONDI);
  
  semaforoPedoni.attenzione();
  cassaPedoni.suonaLoop();
  vibratorePedoni.accendi();
  
  delay(MINI_PAUSA_MILLISECONDI);
  
  vibratorePedoni.spegni();
};

void setup() {};
