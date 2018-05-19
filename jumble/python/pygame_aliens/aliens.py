
import os.path
import random
import sys

import pygame

from pygame.locals import *

if not pygame.image.get_extended():
    raise SystemExit("Requires the extended image loading from SDL_image")

# Constants
FRAMES_PER_SEC = 40
PLAYER_SPEED = 12
MAX_SHOTS = 2
SHOT_SPEED = 10
ALIEN_SPEED = 12
ALIEN_ODDS = 45
EXPLODE_TIME = 6
SCREENRECT = Rect(0, 0, 640, 480)

# Some globals for friendly access
dirtyrects = []
next_tick = 0
class Img: pass # Container for images
main_dir = os.path.split(os.path.abspath(__file__))[0]


def load_image(file, transparent):
    file = os.path.join(main_dir, "data", file)
    try:
        surface = pygame.image.load(file)
    except pygame.error:
        raise SystemExit("Could not load image \"{file}\" {error}".format(file=file, error=pygame.get_error()))

    if transparent:
        corner = surface.get_at((0, 0))
        surface.set_colorkey(corner, RLEACCEL)
    return surface.convert()


# The logic for all the different sprite types
class Actor(object):
    def __init__(self, image):
        super().__init__()
        self.image = image
        self.rect = image.get_rect()

    def update(self):
        pass

    def draw(self, screen):
        r = screen.blit(self.image, self.rect)
        dirtyrects.append(r)

    def erase(self, screen, background):
        r = screen.blit(background, self.rect, self.rect)
        dirtyrects.append(r)

class Player(Actor):
    def __init__(self):
        super().__init__(Img.player)
        self.alive = 1
        self.reloading = 0
        self.rect.centerx = SCREENRECT.centerx
        self.rect.bottom = SCREENRECT.bottom - 10

    def move(self, direction):
        self.rect = self.rect.move(direction*PLAYER_SPEED, 0).clamp(SCREENRECT)

class Alien(Actor):
    def __init__(self):
        super().__init__(Img.alien)
        self.facing = random.choice((-1, 1)) * ALIEN_SPEED
        if self.facing < 0:
            self.rect.right = SCREENRECT.right

    def update(self):
        global SCREENRECT
        self.rect[0] = self.rect[0] + self.facing
        if not SCREENRECT.contains(self.rect):
            self.facing = -self.facing
            self.rect.top = self.rect.bottom + 3
            self.rect = self.rect.clamp(SCREENRECT)

class Explosion(Actor):
    def __init__(self, actor):
        super().__init__(Img.explosion)
        self.life = EXPLODE_TIME
        self.rect.center = actor.rect.center

    def update(self):
        self.life = self.life - 1


class Shot(Actor):
    def __init__(self, player):
        super().__init__(Img.shot)
        self.rect.centerx = player.rect.centerx
        self.rect.top = player.rect.top - 10

    def update(self):
        self.rect.top = self.rect.top - SHOT_SPEED


def main():
    global dirtyrects

    pygame.init()
    screen = pygame.display.set_mode(SCREENRECT.size, 0)
    clock = pygame.time.Clock()

    Img.background = load_image("background.gif", 0)
    Img.shot = load_image("shot.gif", 1)
    Img.bomb = load_image("bomb.gif", 1)
    Img.danger = load_image("danger.gif", 1)
    Img.alien = load_image("alien1.gif", 1)
    Img.player = load_image("oldplayer.gif", 1)
    Img.explosion = load_image("explosion1.gif", 1)

    # Create background
    background = pygame.Surface(SCREENRECT.size)
    for x in range(0, SCREENRECT.width, Img.background.get_width()):
        background.blit(Img.background, (x, 0))
    screen.blit(background, (0, 0))
    pygame.display.flip()

    player = Player()
    aliens = [Alien()]
    shots = []
    explosions = []

    while player.alive or explosions:
        clock.tick(FRAMES_PER_SEC)

        pygame.event.pump()
        keystate = pygame.key.get_pressed()
        if keystate[K_ESCAPE] or pygame.event.peek(QUIT):
            break

        for actor in [player] + aliens + shots + explosions:
            actor.erase(screen, background)
            actor.update()

        for e in explosions:
            if e.life <= 0:
                explosions.remove(e)

        for s in shots:
            if s.rect.top <= 0:
                shots.remove(s)

        direction = keystate[K_RIGHT] - keystate[K_LEFT]
        player.move(direction)

        if not player.reloading and keystate[K_SPACE] and len(shots) < MAX_SHOTS:
            shots.append(Shot(player))
        player.reloading = keystate[K_SPACE]

        if not int(random.random() * ALIEN_ODDS):
            aliens.append(Alien())

        alienrects = []
        for a in aliens:
            alienrects.append(a.rect)

        hit = player.rect.collidelist(alienrects)

        if hit != -1:
            alien = aliens[hit]
            explosions.append(Explosion(alien))
            explosions.append(Explosion(player))
            aliens.remove(alien)
            player.alive = 0

        for shot in shots:
            hit = shot.rect.collidelist(alienrects)
            if hit != -1:
                alien = aliens[hit]
                explosions.append(Explosion(alien))
                shots.remove(shot)
                aliens.remove(alien)
                break

        for actor in [player] + aliens + shots + explosions:
            actor.draw(screen)

        pygame.display.update(dirtyrects)
        dirtyrects = []

    pygame.time.wait(50)

if __name__ == "__main__":
    main()
