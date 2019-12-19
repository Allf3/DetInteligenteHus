

#define Aktiv_OCRXC OCR5C; // Change OCR5C if you are using a different output

#define Aktiv_Port DDRL; //Defines what PortPin's we want to use. Datasheet 13.3.11

#define Aktiv_OutputPorts (1<<PL5); // Add (1<<PL3) or (1<<Pl4) for use of last OutputPins

void init_Timer5();

void Set_OCR5C(int val);