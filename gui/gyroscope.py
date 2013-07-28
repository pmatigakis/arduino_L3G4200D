import serial
import pygame

SERIAL_PORT = "/dev/ttyACM0"
DPS = 250.0
MAX_DPS_VALUE = float(2**16)
DT = 1.0 / 100.0

width = 640
height = 480
screen_size = (width, height)
black = (0, 0, 0)
red = (255, 0, 0)

pygame.init()

screen = pygame.display.set_mode(screen_size)

serial_port = serial.Serial(SERIAL_PORT)

font = pygame.font.Font(None, 30)

x = 0.0

pos = [i for i in range(640)]
x_data = [0.0 for i in range(640)]

try:
    while True:
        line = serial_port.readline()
        try:
            x_rot, y_rot, z_rot = line.strip().split("\t")
            x_rot = float(x_rot) * (DPS / MAX_DPS_VALUE)

            x += x_rot * DT

            x_data.append(x)
            x_data.pop(0)
        except:
            print("Failed to parse data")

        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                serial_port.close()
                exit()

        screen.fill(black)
        
        adjusted_data = [d + height/2 for d in x_data]

        pygame.draw.lines(screen, red, False, zip(pos, adjusted_data), 5)

        pygame.display.flip()
except KeyboardInterrupt:
    print("Shutting down")
finally:
    serial_port.close()
