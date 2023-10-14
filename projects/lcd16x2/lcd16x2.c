/* lcd I2C program
 * 
 * This program shows how to use /dev/i2c-X to access the lcd.
 * Author.: Paulo da Silva ppsilv @ gmail . com
 * 
 * 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>		
#include <fcntl.h>		
#include <sys/ioctl.h>	
#include <linux/i2c-dev.h>

#define erro printf
//#define debug printf
#define debug //

#define LCD_BACKLIGHT 		0x08
#define LCD_NOBACKLIGHT 	0x00
#define LCD_SETCGRAMADDR 	0x40
#define LCD_SETDDRAMADDR 	0x80

// flags for display on/off control
#define LCD_DISPLAYCONTROL  0x08
#define LCD_DISPLAYON 		0x04
#define LCD_CURSORON 		0x02
#define LCD_BLINKON 		0x01
#define LCD_DISPLAYOFF 		0x00
#define LCD_CURSOROFF 		0x00
#define LCD_BLINKOFF 		0x00


unsigned char _Addr;
unsigned char _displayfunction;
unsigned char _displaycontrol;
unsigned char _displaymode;
unsigned char _numlines = 2;
unsigned char _cols;
unsigned char _rows;
unsigned char _backlightval;
unsigned char _objFileName[256]={"/dev/i2c-2"};

const unsigned char		lcd2Lines	= 0x28;    //use 2 line and initialize 5*7 matrix in (4-bit mode)
const unsigned char		lcdClear	= 0x01;    //clear display screen
const unsigned char		lcdOn		= 0x0C;    //display on cursor off
const unsigned char		lcdEntryMode= 0x06;    //cursor increment
const unsigned char		lcdBacklight= 0x10;    //Backlight on
const unsigned char		lcdCursor	= 0x06;    //increment cursor (shift cursor to right)

const unsigned char		cmdEnHigh = 0x04;
const unsigned char		dataEnHigh = 0x05;

int fi2c =0x0;
//Prototypes
void lcdWriteCommand(unsigned char cmd);
void lcdWriteChar(unsigned char chr);

int openDevice()
{
	fi2c = open(_objFileName, O_WRONLY);
	if ( fi2c < 0 ){
		erro("Error openning file...\n");
		return(1);
	}
	//<<<<<The I2C address of the slave
	if( _Addr == 0x0 ){
		erro("Error slave addr not set...\n");
		return(1);
	}
	if (ioctl( fi2c, I2C_SLAVE, _Addr) < 0)
	{
		erro("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return(1);
	}	
    debug("Teste de device open file[%u]\n",fi2c);
    return(0);
}

void writeDevice(unsigned char data)
{
	write(fi2c,(const void *)&data,1);
}

void clear(){
	lcdWriteCommand(lcdClear);
}

void lcdWriteChar(unsigned char chr)
{
	unsigned char idata = 0x00;
	//High nibble
	idata |= ((0xF0 & chr) | dataEnHigh); //Set CMD and E = 1
	debug("nibble 0 E=1[%02X] ",idata);
	writeDevice(idata);
	usleep(5000);
	idata &= ~dataEnHigh;  //Set CMD and E = 0
	idata |= (0x01 );
	debug("nibble 0 E=0[%02X] ",idata);
	writeDevice(idata);
	
	idata = 0x0;

	//Low nibble
	idata |= (( chr << 4 ) | dataEnHigh); //Set CMD and E = 1
	debug("nibble 1 E=1[%02X] ",idata);
	writeDevice(idata);
	usleep(5000);
	idata &= ~dataEnHigh;  //Set CMD and E = 0
	idata |= (0x01 | _backlightval);
	debug("nibble 1 E=0[%02X]\n",idata);
	writeDevice(idata);
}

void lcdWriteCommand(unsigned char cmd)
{
	unsigned char idata = 0x00;

	//High nibble
	idata |= ((0xF0 & cmd) | cmdEnHigh); //Set chr and E = 1
	debug("nibble 0 E=1[%02X] - ",idata);
	writeDevice(idata);
	usleep(5000);
	idata &= ~cmdEnHigh;  //Set chr and E = 0
	debug("E=0[%02X] -",idata);
	writeDevice(idata);

	idata = 0x0;

	//Low nibble
	idata |= (( cmd << 4 ) | cmdEnHigh); //Set chr and E = 1
	debug("nibble 1 E=1[%02X] - ",idata);
	writeDevice(idata);
	usleep(5000);
	idata &= ~cmdEnHigh;  //Set chr and E = 0
	idata |= _backlightval;
	debug("E=0[%02X]\n",idata);
	writeDevice(idata);
}
void lcdWriteCommand1(unsigned char cmd)
{
	unsigned char idata = 0x00;

	//High nibble
	idata |= ((0xF0 & cmd) | cmdEnHigh); //Set chr and E = 1
	debug("nibble 0 E=1[%02X] - ",idata);
	writeDevice(idata);
	usleep(5000);
	idata &= ~cmdEnHigh;  //Set chr and E = 0
	debug("E=0[%02X] \n",idata);
	writeDevice(idata);
}

void setCursor(unsigned char col, unsigned char row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}
	lcdWriteCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}
void cursorOff()
{
	debug("Cursor off ");
	_displaycontrol = _displaycontrol & (~LCD_CURSORON) ;
	lcdWriteCommand( _displaycontrol );
}
void cursorOn()
{
	debug("Cursor on ");
	lcdWriteCommand( (_displaycontrol |=  LCD_CURSORON ) );
}
void cursorBlinkOff()
{
	debug("Cursor off ");
	_displaycontrol = _displaycontrol & (~LCD_BLINKON) ;
	lcdWriteCommand( _displaycontrol );
}
void cursorBlinkOn()
{
	debug("Cursor on ");
	lcdWriteCommand( (_displaycontrol |=  LCD_BLINKON ) );
}
void noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	lcdWriteCommand(_displaycontrol);
}
void display() {
	_displaycontrol |= LCD_DISPLAYON;
	lcdWriteCommand(_displaycontrol);
}




void writeStr(unsigned char * str)
{
	unsigned char * s = str;
	while( *s ){
		lcdWriteChar(*s++);
	}
}

void closeDevice()
{
	close(fi2c);
}	

void lcdCmd()
{
	sleep(1);
	
	_backlightval = LCD_BACKLIGHT;
	
	_displaycontrol = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
	
	_Addr = 0x27;	
	memcpy(_objFileName ,"/dev/i2c-2",sizeof("/dev/i2c-2"));
	if( ! openDevice() ){
		
		debug("Inicializando display [0x30] ");
		lcdWriteCommand(0x30);	
 		usleep(4100); // wait min 4.1ms
		debug("Inicializando display [0x30] ");
		lcdWriteCommand(0x30);	
 		usleep(100); // wait min 4.1ms
		debug("Inicializando display [0x30] ");
		lcdWriteCommand(0x30);	

		debug("Inicializando display [0x20] ");
		lcdWriteCommand1(0x20);	
		debug("Inicializando display [%02X] ",lcd2Lines);
		lcdWriteCommand(lcd2Lines);	


		debug("backlight display.... [%02X] ",lcdBacklight);
		lcdWriteCommand(lcdBacklight);
 		usleep(4500); 

		debug("Clear display........ [%02X] ",lcdClear);
		clear();
 		usleep(4500); 

		debug("display ON........... [%02X] ",lcdOn);
		//lcdWriteCommand(lcdOn);
		lcdWriteCommand(_displaycontrol);
 		usleep(4500); 
		
		debug("Entry mode display..  [%02X] ",lcdEntryMode);
		lcdWriteCommand(lcdEntryMode);
 		usleep(4500); 
		
		/*
		lcdWriteChar('O');
		lcdWriteChar('r');
		lcdWriteChar('a');
		lcdWriteChar('n');
		lcdWriteChar('g');
		lcdWriteChar('e');
		
		setCursor(0,1);
		writeStr("PI 5 plus");
		*/
	}
} 
// Store the content of the file
char myString[100];

void readFile()
{
	FILE *fptr;
	
	// Open a file in read mode
	fptr = fopen("/etc/hostname", "r");
	
	
	// Read the content and store it inside myString
	fgets(myString, 100, fptr);
	
	// Print the file content
	printf("%s", myString);
	
	// Close the file
	fclose(fptr);	
}

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed)
{
getifaddrs(&addrs);
tmp = addrs;	
  while (*str_untrimmed != '\0')
  {
    if(!isspace(*str_untrimmed))
    {
      *str_trimmed = *str_untrimmed;
      str_trimmed++;
    }
    str_untrimmed++;
  }
  *str_trimmed = '\0';
}

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>


void getIP()
{
getifaddrs(&addrs);
tmp = addrs;

while (tmp) 
{
    if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
    {
        struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
        printf("%s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
    }

    tmp = tmp->ifa_next;
}

freeifaddrs(addrs);	
	
}
int main()
{
	char buf[32];
	printf("Teste I2C orange pi 5 plus...\n");

	lcdCmd();	
	readFile();
	remove_spaces(buf,myString);
	printf("Nome maquina [%s]\n",buf);	
	writeStr("Maquina ");
	writeStr(buf);	
	setCursor(0,1);
	writeStr("IP:192.168.1.116");

		
	return(0);
}

