import os
import sys
import time
import random
import pygame

# Vérifier si le fichier blockchain.log existe
LOG_FILE = os.path.expanduser("~/blockchain_cpp/blockchain.log")

if not os.path.exists(LOG_FILE):
    print(f"❌ Fichier introuvable : {LOG_FILE}")
    sys.exit(1)

# Initialisation de Pygame
pygame.init()

# Dimensions de la fenêtre
WIDTH, HEIGHT = 800, 600
FONT_SIZE = 20
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Blockchain Matrix")

# Couleurs
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)

# Police de caractères
font = pygame.font.Font(pygame.font.match_font('monospace'), FONT_SIZE)

# Lire les transactions de la blockchain
with open(LOG_FILE, "r") as f:
    transactions = [line.strip() for line in f.readlines() if "Data:" in line]

# Générer des colonnes de texte défilant
columns = [random.randint(0, WIDTH // FONT_SIZE) for _ in range(len(transactions))]
positions = [random.randint(-HEIGHT, 0) for _ in range(len(transactions))]

running = True
clock = pygame.time.Clock()

while running:
    screen.fill(BLACK)

    for i in range(len(transactions)):
        text_surface = font.render(transactions[i], True, GREEN)
        x = columns[i] * FONT_SIZE
        y = positions[i]
        screen.blit(text_surface, (x, y))

        positions[i] += FONT_SIZE // 2  # Vitesse du défilement

        if positions[i] > HEIGHT:
            positions[i] = random.randint(-HEIGHT, 0)

    pygame.display.flip()
    clock.tick(15)  # FPS

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

pygame.quit()

