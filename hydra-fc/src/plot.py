# Library
import matplotlib.pyplot as plt
import serial

# Initialise serial connection
s = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

# Store Data
x = 0
time_values = []
temperature_values = []
pressure_values = []

# Main Program Loop
try:
    while True:

        # Read data stream from serial
        a = s.readline().decode().strip()

        # Skip empty lines
        if not a:
            continue  
    
        # Parse line for data
        try:
            if "Temperature" in a:
                temperature = float(a.split('=')[1].split()[0])
                temperature_values.append(temperature)
                print(f"Temperature: {temperature}")
                
            elif "Pressure" in a:
                pressure = float(a.split('=')[1].split()[0])
                pressure_values.append(pressure)
                print(f"Pressure: {pressure}")
                
            # Update the time values list
            time_values.append(x)
            x += 1
        
        except (ValueError, IndexError) as e:
            print(f"Could not convert data: {a} | Error: {e}")

except KeyboardInterrupt:
    print("Script interrupted by user.")