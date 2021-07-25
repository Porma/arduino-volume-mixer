import serial

from mixer import Mixer


def main():
    print("Hello world")

    arduino = serial.Serial(port="COM7", baudrate=115200, timeout=0.01)

    mixer = Mixer()

    while True:
        if arduino.in_waiting > 0:
            cmd = arduino.read(2).decode('UTF-8')
            # print(cmd)
            mixer.process_input(cmd)


if __name__ == '__main__':
    main()

