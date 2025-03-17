import curses
import random
import time

def matrix_effect(stdscr):
    """ Effet Matrix fluide et stable, sans clignotement """
    curses.start_color()
    curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)  # Vert normal
    curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLACK)  # Blanc lumineux
    curses.init_pair(3, curses.COLOR_GREEN, curses.COLOR_BLACK)  # Vert foncé (traînée)

    stdscr.nodelay(1)
    stdscr.timeout(50)

    height, width = stdscr.getmaxyx()
    num_columns = width // 2
    drops = [random.randint(-height, 0) for _ in range(num_columns)]
    trails = [[" " for _ in range(height)] for _ in range(num_columns)]

    while True:
        for i in range(num_columns):
            x = i * 2
            y = drops[i]

            char = random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()")

            # **Ne pas effacer l’écran !**
            if 0 <= y < height:
                trails[i][y] = char
                stdscr.addstr(y, x, char, curses.color_pair(2) if random.random() > 0.98 else curses.color_pair(1))

                # **Créer un effet de traînée fluide**
                for j in range(1, 6):  # Longueur de la traînée
                    if y - j >= 0:
                        stdscr.addstr(y - j, x, trails[i][y - j], curses.color_pair(3))

            drops[i] += 1

            if drops[i] >= height:
                drops[i] = random.randint(-height // 2, 0)  # Réapparition en haut, doucement

        stdscr.refresh()
        time.sleep(0.07)  # Légère pause pour lisser l'animation

        key = stdscr.getch()
        if key == ord('q'):
            break

curses.wrapper(matrix_effect)





