*This project has been created as part of the 42 curriculum by mmubina.*

# cub3D

## Description

cub3D is my first RayCaster built with the **miniLibX** library. Inspired by the
world-famous *Wolfenstein 3D* (Id Software, 1992) — considered the first true
FPS — the goal is to render a "realistic" 3D first-person view of the inside of
a maze using ray-casting techniques.

The program reads a scene description file (`*.cub`), parses the map and its
configuration, and renders a dynamic view where the player can move and look
around. Walls are textured differently depending on the side they face
(North, South, East, West), and the floor and ceiling are filled with two
configurable colors.

## Instructions

### Build

```bash
make        # build the mandatory program (cub3D)
make bonus  # build the bonus version
make clean  # remove object files
make fclean # remove object files and the binary
make re     # full rebuild
```

The Makefile compiles with `-Wall -Wextra -Werror` using `cc`, builds `libft`
and the `minilibx` from their own Makefiles, and does not relink unnecessarily.

### Run

```bash
./cub3D maps/example.cub
```

The program takes a single argument: a scene description file with the `.cub`
extension.

### Controls

| Key            | Action                          |
|----------------|---------------------------------|
| `W` `A` `S` `D`| Move through the maze           |
| `←` `→`        | Look left / right               |
| `ESC`          | Close the window and quit       |
| Red cross      | Close the window and quit       |

### Scene file (`.cub`) format

```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0          # floor color   R,G,B in [0,255]
C 225,30,0           # ceiling color R,G,B in [0,255]

1111111111
1000000001
10000N0001
1111111111
```

- Map characters: `0` (empty), `1` (wall), `N/S/E/W` (player start + orientation),
  and spaces.
- Elements (`NO SO WE EA F C`) may appear in any order; the map must be last.
- The map must be closed/surrounded by walls.
- On any misconfiguration the program exits cleanly printing `Error\n` followed
  by an explicit message.

## What you need to learn (study roadmap)

A self-study path, in roughly the order it's needed for the build.

### 1. Ray-casting (core math — learn this first)
- The DDA (Digital Differential Analysis) algorithm for stepping a ray through
  grid cells until it hits a wall.
- Camera plane vs. direction vector, and how FOV is represented by two vectors.
- Perpendicular wall distance (avoids the "fish-eye" effect).
- Computing each vertical stripe's line height from the distance.
- Texture mapping: `wallX`, picking the texture column, stepping texture Y.
- Distinguishing N/S/E/W wall faces to choose the right texture.

### 2. MiniLibX (graphics)
- Window/image creation: `mlx_init`, `mlx_new_window`, `mlx_new_image`.
- Drawing into an image buffer via `mlx_get_data_addr` (write pixels manually —
  never `mlx_pixel_put` per pixel, it's far too slow).
- Loading XPM textures: `mlx_xpm_file_to_image` + `mlx_get_data_addr`.
- Event hooks: `mlx_hook` / `mlx_loop_hook`, key codes, clean window close
  (the red cross, `DestroyNotify` / event 17).
- `bits_per_pixel`, `line_length`, `endian` for correct pixel indexing.

### 3. Linear algebra / trig basics
- 2D vectors and vector rotation (rotation matrix) for turning the view.
- `sin`, `cos`, `atan2`, and the `-lm` math library.
- Mapping a grid to world space.

### 4. Parsing (a large part of the grade)
- Reading the file line by line (`open`/`read` or `get_next_line`).
- Validating the 6 elements in any order, separated by spaces/empty lines.
- Map validation: allowed chars only, exactly one player, and a flood-fill
  check that the map is fully closed.
- Robust error handling: clean exit, no leaks, no crashes.

### 5. C fundamentals & 42 norm
- The 42 Norm (function length, variable limits, etc.).
- Memory management: `valgrind` for zero leaks; free MLX resources
  (`mlx_destroy_image`, `mlx_destroy_window`, `mlx_destroy_display`).
- Makefile: `all clean fclean re bonus`, no relinking, libft + mlx builds.

**Suggested order:** C/Makefile/norm refresher → MiniLibX (pixel, image, keys)
→ ray-casting (untextured walls, then textures) → movement & rotation →
parsing + flood fill.

## Resources

- **Lode Vandevenne — Raycasting tutorial** (the reference for this project):
  https://lodev.org/cgtutor/raycasting.html
- **42 Docs — MiniLibX guide:**
  https://harm-smits.github.io/42docs/libs/minilibx
- **Original Wolfenstein 3D** (to test before starting): http://users.atw.hu/wolf3d/
- Flood-fill algorithm references for the map-closure check.

### Use of AI

AI was used as a study aid to **understand** concepts (the DDA loop, perpendicular
distance, flood-fill map validation) and to draft documentation such as this
README. All implementation logic was reviewed, tested, and is fully understood —
in line with the 42 AI guidelines, so that every part can be explained and
modified during the peer evaluation.
