///////////////////////////////////////////////////////////////////
///////         MEDIDOR DE ENERGIA  V 1.0      ////////////////////
///////                                        ////////////////////
/////// Ultima Atualização - 18/12/2017        ////////////////////
///////                                        ////////////////////
/////// Mede: tensão; corrente; frequencia;    ////////////////////
//////  Fase                                   ////////////////////
/////// calcula: energia, potenciaAparente     ////////////////////
/////// Fator de Pot.                          ////////////////////
/////// Atl. Funçoes                           ////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//    Pino entrada do sensor de corrente:  A0                    //
//    Pino entrada do sensor de  Nivel CC da corrente:  A1       //
//                                                               //   
//    Pino entrada do sensor de tensao:  A5                      //
//    Pino entrada do sensor de Nivel CC da tensao:  A4          //
//                                                               //
//    Interrupção 1:  pino 02                                    //
//    Interrupção 2:  pino 03                                    //
//                                                               // 
///////////////////////////////////////////////////////////////////

#include <FreqCount.h>

long tempo1 =0, tempo2 = 0, tempo3 = 0;
float Corrente = 0;
float Tensao = 0; 
float Fator_Potencia = 0;
float Frequencia = 0;
float Potencia_W = 0;
float Potencia_Ativa=0;
float Potencia_Reativa = 0;

float valor_real = 0;
float valor_corrente_real = 0;
float Valor_corrente_RMS = 0;
float Valor_TENSAO_RMS = 0;
float valor_TENSAO_real = 0;
float potencia = 0;
float energia = 0;

unsigned long count = 0;
unsigned int pulso=0;

float Angulo_Def = 0;
float CosFi = 0;

boolean Nivel_Corrente = LOW;
boolean Nivel_Tensao =  LOW; 
boolean Carga = LOW;


const int Pino_Sensor_Corrente = A0;  
const int Pino_Sensor_de_Tensao = A5;
const int Pino_Sensor_Nivel_DC = A4;
const int Pino_Sensor_Nivel_AC = A1;

int Nivel_DC = 0;
int Nivel_AC = 0;
int Sensor_DC = 0;
int Sensor_AC = 0;
int sensorValue = 0;       
int outputValue = 0;        

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Corrente_HIGH()  // interrução nivel alto de corrente
{
   tempo1 = micros();

   pulso++;
   Nivel_Corrente = HIGH; 

     if(Nivel_Tensao == HIGH)
       {
        Carga = HIGH;
        Nivel_Tensao == LOW;
       }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tensao_HIGH()   // interrução nivel alto de tensão
{
  tempo2 = micros();
  Nivel_Tensao = HIGH;
 
    if(Nivel_Corrente == HIGH)
      {
        Carga = LOW;
        Nivel_Corrente == LOW;
      }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float LerFrequencia()
{

 if (FreqCount.available()) 
  {
    count = FreqCount.read();
  }

   return count; 
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float LerCorrente()
{

 for(int a=0;a<=1000;a++)
  {
    Sensor_AC = analogRead(Pino_Sensor_Corrente);            
    Nivel_AC = analogRead(Pino_Sensor_Nivel_AC);            

    valor_corrente_real = Sensor_AC*0.006640625 - (Nivel_AC*0.006640625); 

    delayMicroseconds(1);
    
    Valor_corrente_RMS = Valor_corrente_RMS + valor_corrente_real*valor_corrente_real;
  }
     
   Valor_corrente_RMS = sqrt(Valor_corrente_RMS/1000);
   return Valor_corrente_RMS;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float LerTensao()
{


for(int b=0;b<=1000;b++)
  {
    Sensor_DC = analogRead(Pino_Sensor_de_Tensao);            
    Nivel_DC = analogRead(Pino_Sensor_Nivel_DC);


    valor_TENSAO_real = Sensor_DC*0.60742187 - (Nivel_DC*0.60742187); 

    delayMicroseconds(1);
 
    Valor_TENSAO_RMS = Valor_TENSAO_RMS + valor_TENSAO_real*valor_TENSAO_real;
  }
     
   Valor_TENSAO_RMS = sqrt(Valor_TENSAO_RMS/1000);

   Valor_TENSAO_RMS = Valor_TENSAO_RMS*5; // fator de correção

   return Valor_TENSAO_RMS; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float CalcPotAparente()
{

  potencia  = Valor_TENSAO_RMS*5*Valor_corrente_RMS;  
  return potencia;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float CalPotAtiva()
{
    return potencia*cos(Angulo_Def);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float CalPotReativa()
{
    return potencia*sin(Angulo_Def);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float LerFase()
{

attachInterrupt(0,Tensao_HIGH,RISING); //Configurando a interrupção //pino 02
attachInterrupt(1,Corrente_HIGH,RISING); //Configurando a interrupção   // pino 03


if(pulso >= 3)
{
tempo3 = tempo2-tempo1;


  Angulo_Def = tempo3*2*3.14159*0.000001*60;
  CosFi = cos(Angulo_Def);
 
   detachInterrupt(0);
   detachInterrupt(1);

    pulso = 0;
   
    return CosFi;

}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
 Serial.begin(9600);
 FreqCount.begin(1000); 
}


void loop()
{

Corrente = LerCorrente();

Serial.print("Corrente = " );                       
Serial.print(Corrente, 3);
Serial.print("A");

Tensao = LerTensao();

Serial.print("  Tensão = " );                       
Serial.print(Tensao, 2);
Serial.print("V");

Potencia_W = CalcPotAparente();

Serial.print(" Pot Apr = " );                       
Serial.print(Potencia_W);
Serial.print("VA");  


Potencia_Ativa = CalPotAtiva();

Serial.print(" Pot Ativa = "); 
Serial.print(Potencia_Ativa); 
Serial.print("W");

Potencia_Reativa = CalPotReativa();

Serial.print(" Pot Reat = "); 
Serial.print(Potencia_Reativa); 
Serial.print("Var");


Frequencia = LerFrequencia();

Serial.print(" Freq = ");
Serial.print(Frequencia,2);
Serial.print("Hz");

Fator_Potencia = LerFase();

Serial.print(" FP = "); 
Serial.print(Fator_Potencia); 

if(Carga == HIGH) 
  {
    Serial.print("  Carga Indutiva");
  }else
   {
      Serial.print("  Carga Capacitiva");
   }


Serial.println("");
}

