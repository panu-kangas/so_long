# 💎 Diamond Hunt (so_long)

**Diamond Hunt** is a retro-style 2D puzzle adventure game where you guide a determined king through a maze to recover his stolen diamonds. But beware — cunning evil pigs guard the treasure!  
Thankfully, the King’s trusty Hammer is by his side, ready to smash any trouble that comes his way.

Oh, and heads up — once you’ve collected all the diamonds, there’s a nasty little surprise waiting on your way back... so count your steps when you head for the exit!

## 🛠️ Build Instructions (how to play the game)

⚠️ **NOTE:**  
Diamond Hunt is only verified to work on macOS, and it should also run on Linux.  
Sadly, it does not work on Windows for now.

To build and run **Diamond Hunt**, follow these steps:

1. **Clone the repository:**

    ```bash
    git clone https://github.com/panu-kangas/so_long.git
    cd so_long
    ```

2. **Build the project:**

   Run the following command in the project root:

    ```bash
    make bonus
    ```

4. **Run the game:**

   Run the executable and give it one map from maps/ directory as an argument.
   For example:
   
    ```bash
    ./so_long maps/map1.ber
    ```

## 🧩 Project Details

- 🧠 **Solo project** completed during my studies at [Hive Helsinki](https://www.hive.fi/en/)
- 💻 **Language & Tools:** C and the MLX42 graphics library
- 🕹️ **Key Features:**
  - Sprite rendering & animation
  - Event handling (keyboard input)
  - Map parsing & validation
  - Enemy AI
  - Level design and dynamic gameplay
- ⏱️ **Development Time:** ~5 weeks
- 🕹️ **My very first game ever!**

## 🚀 What I Learned

- Rendering images and animating sprites with MLX42
- Implementing custom enemy movement algorithms
- Core gameplay logic and game loop structure
- Managing memory effectively in C
- Working on a complete game project from start to finish
- Solidified my love for game development ❤️


## 🎮 Controls

- **WASD:** Move the King through the maze
- **H:** Use the Hammer to smash obstacles or enemies
- **Escape:** Exit the game

