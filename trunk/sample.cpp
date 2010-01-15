import Ad;
import 2IoKeypad;
import Uart;
import IntKey;
import Eeprom;
import Lcd1602;

class data;

int main(void)
{
    Scheduler s;
    Data data;
    Ad ad(20 Hz, PA0);
    2IoKeypad io(1000 Hz, PD0, PD1);
    Uart uart(9600 Bps);
    IntKey ik(PB0);
    Eeprom store(256 Bytes);
    Lcd1602 lcd;
    s<<ad<<io<<ik<<uart<<store;
    data.setStore(&store);
    connect(ad.hasData, data.save());
    connect(io.changed, data.save());
    connect(ik.interrupt, data.start());
    connect(uart.connected, data.transfer());
    return 0;
}

class Data
{
public:
    Data(){}
    void setStore(Task* store)
    {
        m_store=store;
    }
    void save()
    {
        m_store.saveByte(inData);
        lcd.clear();
        lcd<<"received: "<<inData;
    }
    void start(){tState=Task_Running;}
    void transfer()
    {
        int i;
        for(i=0;i<store.length;i++)
            uart.send(store[i]);
    }
}
