# Personal Project: Retro 2D RPG Engine

This project is the "base" of a retro RPG, made using C++ and SDL2. 

In it, users can move around an animated character from a top-down perspective and try out a Dragon-Quest-Inspired turn based battle system. However, there is no narrative as this project was meant to be a base that can be built upon to create a more traditional RPG experience.

![Game Screenshot](assets/game_screenshot1.png)

![Game Screenshot](assets/game_screenshot2.png)

---

## Initial Project Goals
- Gain experience with a new programming language (C++)
- Deepen understanding of object-oriented programming
- Explore design patterns
- Develop a graphical windowed application

---

## Project Dependencies   

### [SDL2](https://www.libsdl.org/)   
- Creating and managing the game window.  
- Rendering of textures and sprites.  
- Processing keyboard input for player controls.  

### [SDL2_image](https://wiki.libsdl.org/SDL2_image/FrontPage)
- load and render image files such as **PNG** and **JPG**, which are used for sprites and textures.  

### [SDL2_ttf](https://wiki.libsdl.org/SDL2_ttf/FrontPage)  
- provides support for rendering text using **TrueType Fonts (TTF)**

---

## Architecture Summary

### Finite Hierarchical State Machine  
The project employs a **finite hierarchical state machine** to manage different game states.  

#### High-Level Game States:  
- **Title Screen State** – Handles the game's main menu and navigation.  
- **Overworld State** – Manages player movement, environment interaction, and transitioning into battles.  
- **Battle State** – Controls the battle system, handling player and enemy actions.  

#### Battle Substates:  
Within the **Battle State**, multiple substates manage different aspects of combat:  
- **Battle Menu State** – Displays options for the player (Attack, Arts, Items, etc.).  
- **Battle Action State** – Executes player and enemy actions, processes damage, and checks battle conditions.  
  
### Entity-Component System (ECS)

The project uses the **Entity-Component System (ECS)**. Instead of relying on inheritance and polymorphism to define an entity's properties and behavior, ECS organizes game objects into three parts:  

- **Entities** – Simple IDs or containers that hold components.  
- **Components** – Modular data containers that define an entity’s attributes (e.g., `PositionComponent`, `VelocityComponent`).  
- **Systems** – Operate on entities with specific components to apply logic (e.g., `RenderSystem` draws all entities with a `SpriteComponent`).  

---

## Installation  

📥 **[Download Here](https://www.dropbox.com/scl/fo/9kia20ech62zgu7mp1nip/AHGJjZdBeRL2JXMxrG5I6-4?rlkey=zfyrtyikm9fu388mgixgqwse0&st=skxyd0ph&dl=0)**  

### Running the Game  
1. Download and extract the folder.  
2. Run the executable file (`main.exe`).  

Note: This is a Windows-only build. To run the game on macOS or Linux, you will need to compile the project from source using the appropriate development tools for your platform.

---
