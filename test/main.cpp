#include "mbed.h"
#include "uLCD_4DGL.h"

using namespace std::chrono;

InterruptIn button1(D12);
InterruptIn button2(D13);
InterruptIn button3(D11);
AnalogOut anapin(D7);
AnalogIn Ain(A0);
EventQueue lcdqueue(32 * EVENTS_EVENT_SIZE);



Thread t1;
Thread t2;

uLCD_4DGL uLCD(D1,D0,D2);

int choice = 0;
int output;
float ADCdata[200];
int sample = 200;


void confirm()
{
    output=choice;
    int i;
    for (i = 0; i < sample; i++){
    ADCdata[i] = Ain;
    ThisThread::sleep_for(1000ms/sample);
  }
    for (i = 0; i < sample; i++){
    printf("%f\r\n", ADCdata[i]);
    ThisThread::sleep_for(100ms);
  }
}

void ulcd()
{
    switch(choice){
        case 0:
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.locate(0,0);
            uLCD.color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/2\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/4\n");
            uLCD.textbackground_color(GREEN);
            uLCD.printf("1/8\n");
            break;
        case 1:
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.locate(0,0);
            uLCD.color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/2\n");
            uLCD.textbackground_color(GREEN);
            uLCD.printf("1/4\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/8\n");
            break;
        case 2:
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.locate(0,0);
            uLCD.color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1\n");
            uLCD.textbackground_color(GREEN);
            uLCD.printf("1/2\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/4\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/8\n");
            break;   
        case 3:
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.locate(0,0);
            uLCD.color(WHITE);
            uLCD.textbackground_color(GREEN);
            uLCD.printf("1\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/2\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/4\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/8\n");
            break;   
        default: 
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.locate(0,0);
            uLCD.color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/2\n");
            uLCD.textbackground_color(WHITE);
            uLCD.printf("1/4\n");
            uLCD.textbackground_color(GREEN);
            uLCD.printf("1/8\n");
            break;
    }    
}

void up()
{
	if(choice == 3)
		{choice = 3;
}else
	{choice++;}
lcdqueue.call(ulcd);  

}

void down()
{
if(choice == 0)
		{choice = 0;
}else
	{choice--;}
lcdqueue.call(ulcd);      
}    
    
    
void squre()
{
    float i;

    while(1)
    {
        if (output == 3)
        {
            for(i = 0; i <= 1; i += 0.00141)
            {
                anapin.write(i);
                wait_us(100);
            }
            anapin.write(1);
            ThisThread::sleep_for(80ms);    
            for(i = 1; i >= 0; i -= 0.00141)
            {
                anapin.write(i);
                wait_us(100);
            } 
        }

        if (output == 2)
        {
            for(i = 0; i <= 1; i += 0.00282)
            {
                anapin.write(i);
                wait_us(100);
            }
            anapin.write(1);
            ThisThread::sleep_for(160ms);    
            for(i = 1; i >= 0; i -= 0.00282)
            {
                anapin.write(i);
                wait_us(100);
            } 
        }
        if (output == 1)
        {
            for(i = 0; i <= 1; i += 0.00564)
            {
                anapin.write(i);
                wait_us(100);
            }
            anapin.write(1);
            ThisThread::sleep_for(200ms);    
            for(i = 1; i >= 0; i -= 0.00564)
            {
                anapin.write(i);
                wait_us(100);
            } 
        }
        if (output == 0)
        {
            for(i = 0; i <= 1; i += 0.01128)
            {
                anapin.write(i);
                wait_us(100);
            }
            anapin.write(1);
            ThisThread::sleep_for(220ms);    
            for(i = 1; i >= 0; i -= 0.01128)
            {
                anapin.write(i);
                wait_us(100);
            } 
        }
    }
}
    


int main()
{
  
    //t3.start(callback(&lcdqueue, &EventQueue::dispatch_forever));
    t2.start(squre);
    t1.start(callback(&lcdqueue, &EventQueue::dispatch_forever));
    

    button1.rise(up);
    button2.rise(down);
    button3.rise(lcdqueue.event(confirm));

}