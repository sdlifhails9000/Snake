import curses
import time
from enum import Enum

class Direction(Enum):
    UP = 0
    LEFT = 1
    DOWN = 2
    RIGHT = 3

def main(stdscr):
    KEY_TO_DIR = {
        "w": Direction.UP,
        "a": Direction.LEFT,
        "s": Direction.DOWN,
        "d": Direction.RIGHT
    }
    rows, cols = stdscr.getmaxyx()
    user_input, old_input = -1, -1
    score = 0
    direction = Direction.RIGHT
    coord = [int(cols/ 2), int(rows / 2)]

    stdscr.nodelay(True)

    while True:
        t0 = time.monotonic()
        while time.monotonic() - t0 <= .25:
            user_input = stdscr.getch()
            if user_input == curses.ERR:
                continue

            user_input = chr(user_input)
            if user_input not in KEY_TO_DIR.keys():
                continue

            user_input = KEY_TO_DIR[user_input]
            if (user_input.value + 2) % 4 == direction.value:
                continue
            elif user_input != direction:
                direction = user_input
                break

        match direction:
            case Direction.UP:
                coord[1] -= 1
            case Direction.LEFT:
                coord[0] -= 1
            case Direction.DOWN:
                coord[1] += 1
            case Direction.RIGHT:
                coord[0] += 1
        
        stdscr.erase()
        stdscr.border("|", "|", "-", "-", "/", "\\",
                      "\\", "/")
        stdscr.addstr(1, 1, f"Score: {score}") 
        

        stdscr.addch(coord[1], coord[0], "#")

        old_input = user_input
        stdscr.refresh()


if __name__ == "__main__":
    curses.wrapper(main)

