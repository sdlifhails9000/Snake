import curses

from copy import copy
from random import seed, randint
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
    rows, cols = stdscr.getmaxyx()
    snake = [
        Coord(cols // 2, rows // 2),
        Coord(cols // 2 - 1, rows // 2)
    ]
    direction = 3
    new_dir = 0
    is_dead = False

    seed(monotonic())
    stdscr.nodelay(True)
    curses.curs_set(0)

    while not is_dead:
        ########## Input and timing
        t0 = monotonic()
        while monotonic() - t0 <= .25:
            user_input = stdscr.getch()
            if user_input == curses.ERR:
                continue

            match chr(user_input):
                case "w":
                    new_dir = 0
                case "a":
                    new_dir = 1
                case "s":
                    new_dir = 2
                case "d":
                    new_dir = 3
                case _:
                    continue:

            if (new_dir + 2) % 4 == direction\
                    or new_dir  == direction:
                continue

            direction = new_dir
            break 

        ########## Game logic
        snake.pop()
        snake.insert(1, copy(snake[0]))

        match direction:
            case 0:
                snake[0].y -= 1
            case 1:
                snake[0].x -= 1
            case 2:
                snake[0].y += 1
            case 3:
                snake[0].x += 1

        is_dead = snake[0].x % (cols - 1) == 0\
                or (snake[0].y - 2) % (rows - 3) == 0\
                or snake[0] in snake[1:]

        if snake[0] == food:
            snake.append(snake[-1])
            food = Coord()
            food.x = randint(1, cols - 2)
            food.y = randint(3, rows - 2)
            while food in snake:
                food.x = randint(1, cols - 2)
                food.y = randint(3, rows - 2)

        ########## Output
        stdscr.erase()
        stdscr.border("|", "|", "-", "-", "+", "+", "+", "+")
        stdscr.hline(2, 1, "-", cols - 2)
        stdscr.addstr(1, 1, f"Score: {len(snake) - 1}")

        stdscr.addch(food.y, food.x, "*")

        for i in range(1, len(snake)):
            stdscr.addch(snake[i].y, snake[i].x, "+" if is_dead else "#")

        stdscr.addch(snake[0].y, snake[0].x, "X" if is_dead else "O")

        stdscr.refresh()

    stdscr.nodelay(False)
    stdscr.addstr(1, cols // 2, "You've lost")
    stdscr.getch()


if __name__ == "__main__":
    curses.wrapper(main)

