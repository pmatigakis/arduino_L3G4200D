import serial
import pygame

SERIAL_PORT = "/dev/ttyACM0"
DPS = 250.0
MAX_DPS_VALUE = float(2**16)

screen_size = (320, 240)
black = (0, 0, 0)
red = (255, 0, 0)

pygame.init()

screen = pygame.display.set_mode(screen_size)

serial_port = serial.Serial(SERIAL_PORT)

font = pygame.font.Font(None, 30)

x_sum = 0.0
y_sum = 0.0
z_sum = 0.0

n_samples = 20
cnt = 0

try:
    while True:
        line = serial_port.readline()
        try:
            x_rot, y_rot, z_rot = line.strip().split("\t")
            x_rot = float(x_rot) * (DPS / MAX_DPS_VALUE)
            y_rot = float(y_rot) * (DPS / MAX_DPS_VALUE)
            z_rot = float(z_rot) * (DPS / MAX_DPS_VALUE)            
            cnt += 1
            x_sum += x_rot
            y_sum += y_rot
            z_sum += z_rot
        except:
            print("Failed to parse data")

        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                serial_port.close()
                exit()

        if cnt == n_samples:
            x_rot = x_sum / n_samples
            y_rot = y_sum / n_samples
            z_rot = z_sum / n_samples
            x_sum = 0.0
            y_sum = 0.0
            z_sum = 0.0
            cnt = 0

            screen.fill(black)

            x_rot_text = font.render("X dps: %f" % x_rot, 0, red)
            x_rot_rect = x_rot_text.get_rect()
            x_rot_rect.left = 50

            y_rot_text = font.render("Y dps: %f" % y_rot, 0, red)
            y_rot_rect = y_rot_text.get_rect()
            y_rot_rect.top = 100
            y_rot_rect.left = 50

            z_rot_text = font.render("Z dps: %f" % z_rot, 0, red)
            z_rot_rect = z_rot_text.get_rect()
            z_rot_rect.top = 200
            z_rot_rect.left = 50

            screen.blit(x_rot_text, x_rot_rect)
            screen.blit(y_rot_text, y_rot_rect)
            screen.blit(z_rot_text, z_rot_rect)

            pygame.display.flip()
except KeyboardInterrupt:
    print("Shutting down")
finally:
    serial_port.close()
