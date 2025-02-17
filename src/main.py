import curses
from time import monotonic
import random

# Input and timing: done
# Game logic:
# Output:

class Coord:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def main(stdscr):
    KEY_TO_DIR = {"w": 0, "a": 1, "s": 2, "d": 3}
    rows, cols = stdscr.getmaxyx()
    food = []
    snake = [Coord(cols // 2, rows // 2)]
    direction = 3
    is_dead = False
    t0 = 0.0
    user_input = 0

    random.seed(int(monotonic()))
    stdscr.nodelay(True)
    curses.curs_set(0)

    while not is_dead:
        t0 = monotonic()
        while monotonic() - t0 <= .25:
            user_input = stdscr.getch()
            if user_input == curses.ERR:
                continue

            user_input = chr(user_input)
            if user_input not in KEY_TO_DIR.keys():
                continue

            user_input = KEY_TO_DIR[user_input]
            if (user_input + 2) % 4 == direction\
                    or user_input == direction:
                continue

            direction = user_input
            break 

        match direction:
            case 0:
                snake[0].y -= 1
            case 1:
                snake[0].x -= 1
            case 2:
                snake[0].y += 1
            case 3:
                snake[0].x += 1

        if snake[0].x == 0 or snake[0].x == cols - 1\
                or snake[0].y == 2 or snake[0].y == rows - 1:
            is_dead = True

        if snake[0] in food:
            snake.append(snake[-2] - 2*snake[-1]) 

        stdscr.erase()
        stdscr.border("|", "|", "-", "-", "+", "+", "+", "+")
        stdscr.hline(2, 1, "-", cols - 2)
        stdscr.addstr(1, 1, f"Score: {len(snake) - 1}")

        stdscr.addch(snake[0].y, snake[0].x,
                     "X" if is_dead else "O")

        for s in snake[1:]:
            stdscr.addch(s.y, s.x, "+" if is_dead else "#")

        stdscr.refresh()

    curses.curs_set(1)
    stdscr.nodelay(False)
    stdscr.addstr(rows // 2, 1, "You've lost")
    stdscr.getch()


if __name__ == "__main__":
    curses.wrapper(main)

