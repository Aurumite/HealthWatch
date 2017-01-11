// Timothy Duggan
// Last update: Jan 6 2017
// 
// Most of the psuedo code in comments is directly from the MAX 30100
// datasheet. 
// 
// R and IR are used a lot to refer to infrared and red LEDs which are 
// used to determine blood oxygen levels.
//
// The MAX30100 integrates red and IR LED drivers to drive
// LED pulses for SpO2 and HR measurements.


// Infrared data
uint IR_Data[];
uint R_Data[];


// Reading Data from FIFO
// First transaction: Get the FIFO_WR_PTR:
// START;

I2C_1_Start();
MAX30100_Start(); // Probably not usable with PSoC Creator
UART_1_Start();

// Send device address + write mode
// Send address of FIFO_WR_PTR;
//
// Tim: Not sure why this is necessary. 
// Maybe it initializes the WR_PTR? I don't know.
// Also, I assumed the 0x00 value.
//
// The FIFO write pointer points to the location where the MAX30100 writes the next sample

FIFO_WriteReg(FIFO_WR_PTR, 0x00);

// REPEATED_START;
// Send device address + read mode
// Read FIFO_WR_PTR;

FIFO_ReadReg(FIFO_WR_PTR);

// STOP;



// The central processor evaluates the number of samples to be read from the FIFO:
NUM_AVAILABLE_SAMPLES = FIFO_WR_PTR – FIFO_RD_PTR
// (Note: pointer wrap around should be taken into account)
NUM_SAMPLES_TO_READ = < less than or equal to NUM_AVAILABLE_SAMPLES >



// Second transaction: Read NUM_SAMPLES_TO_READ samples from the FIFO:
// START;
// Send device address + write mode
// Send address of FIFO_DATA;
//
// Tim: Not sure why this is necessary. 
// Maybe it initializes the WR_PTR? I don't know.
// Also, I assumed the 0x00 value.

FIFO_WriteReg(FIFO_DATA, 0x00);


// All of our data should be in the FIFO Register.
// We just need to work on interpreting it. But,
// Temperature, HR, and O2 data should all be in
// this FIFO.

// Reading FIFO_DATA register does not automatically increment the register 
// address; burst reading this register reads the same address over and over. 
// Each sample is 4 bytes of data, so this register has to be read 4 times to 
// get one sample.

// When reading the MAX30100 registers in one burst-read I2C transaction, the 
// register address pointer typically increments so that the next byte of data 
// sent is from the next register, etc. The exception to this is the FIFO data 
// register, register 0x05. When reading this register, the address pointer does 
// not increment, but the FIFO_RD_PTR does. So the next byte of data sent will 
// represent the next byte of data available in the FIFO.


// REPEATED_START;
// Send device address + read mode
for (i = 0 + 1; i < NUM_SAMPLES_TO_READ + 1; i++) {
	// Read FIFO_DATA;
	// Save IR[15:8];
	IR_Data[15*i:8*i] = FIFO_ReadReg(FIFO_Data);
	// Read FIFO_DATA;
	// Save IR[7:0];
	IR_Data[7*i:0] = FIFO_ReadReg(FIFO_Data);
	// Read FIFO_DATA;
	// Save R[15:8];
	R_Data[15*i:8*i] = FIFO_ReadReg(FIFO_Data);
	// Read FIFO_DATA;
	// Save R[7:0];
	R_Data[7*i:0] = FIFO_ReadReg(FIFO_Data);
}
// STOP;

// Third transaction: Write to FIFO_RD_PTR register. If the second transaction was 
// successful, FIFO_RD_PTR points to the next sample in the FIFO, and this third 
// transaction is not necessary. Otherwise, the processor updates the
// FIFO_RD_PTR appropriately, so that the samples are reread.
// START;
// Send device address + write mode
// Send address of FIFO_RD_PTR;
// Write FIFO_RD_PTR;

FIFO_WriteReg(FIFO_RD_PTR, 0x00);

// STOP;