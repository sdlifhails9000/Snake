import curses
import random

from time import monotonic

# Input and timing: done
# Game logic: Done
# Output: Done

class Coord:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    
    def __eq__(self, c):
        return c.x == self.x and c.y == self.y


def main(stdscr):
    KEY_TO_DIR = {"w": 0, "a": 1, "s": 2, "d": 3}
    rows, cols = stdscr.getmaxyx()
    snake = [
        Coord(cols // 2, rows // 2),
        Coord(cols // 2 - 1, rows // 2),
    ]
    direction = 3
    is_dead = False

    random.seed(monotonic())
    stdscr.nodelay(True)
    curses.curs_set(0)

    foods = []
    while not is_dead:
        ########## Input and timing
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

        ########## Game logic
        for i in reversed(range(1, len(snake))):
            snake[i].x = snake[i-1].x
            snake[i].y = snake[i-1].y

        match direction:
            case 0:
                snake[0].y -= 1
            case 1:
                snake[0].x -= 1
            case 2:
                snake[0].y += 1
            case 3:
                snake[0].x += 1

        # Wall collision
        if snake[0].x == 0 or snake[0].x == cols - 1\
                or snake[0].y == 2 or snake[0].y == rows - 1:
            is_dead = True

        # Self collision
        if snake[0] in snake[1:]:
            is_dead = True

        if snake[0] in foods:
            snake.append(
                    Coord(2*snake[-1].x - snake[-2].x,
                          2*snake[-1].y - snake[-2].y))
            foods.remove(snake[0])

        if monotonic() % 5 >= 4.7:
            food = Coord()
            food.x = random.randint(1, cols - 2)
            food.y = random.randint(3, rows - 2)
            if food not in snake and food not in foods:
                foods.append(food)

        ########## Output
        stdscr.erase()
        stdscr.border("|", "|", "-", "-", "+", "+", "+", "+")
        stdscr.hline(2, 1, "-", cols - 2)
        stdscr.addstr(1, 1, f"Score: {len(snake) - 1}")

        for f in foods:
            stdscr.addch(f.y, f.x, "*")

        for i in range(1, len(snake)):
            stdscr.addch(
                snake[i].y, snake[i].x, "+" if is_dead else "#")

        stdscr.addch(snake[0].y, snake[0].x,
                     "X" if is_dead else "O")

        stdscr.refresh()

    stdscr.nodelay(False)
    stdscr.addstr(1, cols // 2, "You've lost")
    stdscr.getch()


if __name__ == "__main__":
    curses.wrapper(main)

