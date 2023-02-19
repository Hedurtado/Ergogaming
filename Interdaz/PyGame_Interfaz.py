import pygame
import sys
pygame.init()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((400, 300))

# Definir los botones del guante
botones_guante = {1: None, 2: None, 3: None, 4: None, 5: None, 6: None, 7: None, 8: None, 9: None, 10: None, 11: None,
                  12: None, 13: None}


# Función para asignar una tecla del teclado a un botón
def asignar_tecla(botón, tecla):
    botones_guante[botón] = tecla


# Bucle principal del programa
while True:
    # Leer la entrada del guante
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            botón_guante = event.button
            # Mostrar en la pantalla qué botón del guante se está configurando
            print("Configurando botón del guante: ", botón_guante)
            # Esperar a que el usuario presione una tecla del teclado
            while True:
                event = pygame.event.wait()
                if event.type == pygame.KEYDOWN:
                    # Asignar la tecla del teclado al botón del guante correspondiente
                    tecla = event.key
                    asignar_tecla(botón_guante, tecla)
                    break
    # Salir del programa si se detecta un evento de cierre
    if event.type == pygame.QUIT:
        pygame.quit()
        sys.exit()
