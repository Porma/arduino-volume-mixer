import serial


def main():
    print("Hello world")

    arduino = serial.Serial(port="COM7", baudrate=115200, timeout=0.01)

    while True:
        if arduino.in_waiting > 0:
            cmd = arduino.read(2).decode('UTF-8')
            print(cmd)


if __name__ == '__main__':
    main()

