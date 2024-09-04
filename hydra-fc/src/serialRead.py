# Library
import matplotlib.pyplot as plt
import serial
import csv

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
x = 0                 # Time counter, currently 500 ms due to main delay in main.cpp
time_values = []      # Stores time counter values  
x_gyro_values = []
y_gyro_values = []
z_gyro_values = []
x_accel_values = []
y_accel_values = []
z_accel_values = []
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
            if "IMU" in a:

                # Extract IMU data
                imu_parts = a.split(':')[1].split()
                x_gyro = float(imu_parts[0])
                y_gyro = float(imu_parts[1])
                z_gyro = float(imu_parts[2])
                x_accel = float(imu_parts[3])
                y_accel = float(imu_parts[4])
                z_accel = float(imu_parts[5])
                
                # Append IMU values
                x_gyro_values.append(x_gyro)
                y_gyro_values.append(y_gyro)
                z_gyro_values.append(z_gyro)
                x_accel_values.append(x_accel)
                y_accel_values.append(y_accel)
                z_accel_values.append(z_accel)

                print(f"IMU Gyro: {x_gyro}, {y_gyro}, {z_gyro} | Accel: {x_accel}, {y_accel}, {z_accel}")

            elif "Temperature" in a:
                temperature = float(a.split(':')[1].split()[0])
                temperature_values.append(temperature)
                print(f"Temperature: {temperature}")
                
            elif "Pressure" in a:
                pressure = float(a.split(':')[1].split()[0])
                pressure_values.append(pressure)
                print(f"Pressure: {pressure}")
                
            # Update the time values list
            time_values.append(x)
            x += 0.5
        
        except (ValueError, IndexError) as e:
            print(f"Could not convert data: {a} | Error: {e}")

except KeyboardInterrupt:
    print("Saving data to CSV...")

    # Writing data to CSV
    with open('src/sensor_data.csv', mode='w', newline='') as file:
        writer = csv.writer(file)
        
        # Write the header
        writer.writerow(['Time (s)', 'X_Gyro (deg/s)', 'Y_Gyro (deg/s)', 'Z_Gyro (deg/s)', 
                         'X_Accel (g)', 'Y_Accel (g)', 'Z_Accel (g)', 'Temperature (C)', 'Pressure (Pa)'])
        
        # Write the data row by row
        for i in range(len(time_values)):
            writer.writerow([
                time_values[i],
                x_gyro_values[i] if i < len(x_gyro_values) else '',
                y_gyro_values[i] if i < len(y_gyro_values) else '',
                z_gyro_values[i] if i < len(z_gyro_values) else '',
                x_accel_values[i] if i < len(x_accel_values) else '',
                y_accel_values[i] if i < len(y_accel_values) else '',
                z_accel_values[i] if i < len(z_accel_values) else '',
                temperature_values[i] if i < len(temperature_values) else '',
                pressure_values[i] if i < len(pressure_values) else ''
            ])
    
    print("Data successfully saved to 'sensor_data.csv'")
    print("Script interrupted by user.")