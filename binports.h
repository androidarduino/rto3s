#ifndef BINPORTS_H
#define BINPORTS_H
#include <avr/io.h>

typedef volatile unsigned char addr;
//TODO: this class hasn't been debugged and tested yet.
class Port: public Task
{
public:
	Port(addr& portAddr, bool invert=false)
	{
		m_port=&portAddr;
		//Assuming cpu==atmega16/32. Modify if cpu has less/more ports.
		if(portAddr==PORTA)m_mode=&DDRA;
		if(portAddr==PORTB)m_mode=&DDRB;
		if(portAddr==PORTC)m_mode=&DDRC;
		if(portAddr==PORTD)m_mode=&DDRD;
		m_invert=invert;
	}
	void setMode(uchar bits)
	{
		*m_mode=bits;
	}
	void outAll(uchar bits)
	{
		if(m_invert)
			bits=~bits;
		setMode(0xff);
		*m_port=bits;
	}
	uchar inAll()
	{
		setMode(0x00);
		uchar t=*m_port;
		return t;
	}
	bool in(uchar bit)
	{
		bit=1<<bit;
		setMode(*m_mode&(~bit));
		uchar t=*m_port&bit;
		return t;
	}
	void out(uchar bit, bool value)
	{
		bit=1<<bit;
		uchar t=1<<bit;
		setMode(*m_mode|t);//1 for out?
		uchar r=*m_mode;
		if(value)
			*m_mode=r|t;
		else
			*m_mode=r&(~t);
	}
private:
	addr * m_port, * m_mode;
	bool m_invert;
};

#endif
