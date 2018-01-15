# ArrowWay
Unity project ArrowWay 

# BombermanTest
A retro 3D Top-Down game of bomberman. 
**This project uses UE 4.18.**


# Player Controls
Player 1: 
  - Move: W, S, A, D. 
  - Drop bomb: Space bar.

Player 2: 
  - Move: Arrows UP, Down, Right and Left.
  - Drop bombs: Numpad + or Enter.


# Pickups (Give players power-ups)
  - Yellow square: Add more bombs.

  - Blue square: Increase bomb blast in 50% (Max 300%).

  - Green square: Increase player speed in 20% (Max 200%).

  - Red square: Activate remote bomb (for 10s.). To explode press the same button to drop the bombs.

# Project's Structure
 
 # Game Instance.
  - BP_BomberGameInstance. 

 # C++ Classes:

  - BombermanGameMode: AGameModeBase.

  - BombermanPlayerController: APlayerController.

  - BombermanCharacter: ACharacter.

  - PickUps: AActor.

  - DestructibleWalls: AActor.

  - Bombs: AActor.

  - DamageInterface: UInterface.

 # Derived  Blueprints from C++ classes.

  - BP_BombermanGameMode: BombermanGameMode.

  - BP_PlayerController: BombermanPlayerController.

  - BP_BomberChar: BombermanCharacter.

  - BP_Pickups: PickUps.

  - BP_Destructible: DestructibleWalls.

  - BP_Bomb: Bombs.

  - BP_RemoteBomb: Bombs, BP_Bomb.

 # Pure Blueprints.

  - BP_MapGenerator.

  - BP_SpawnDestructibleWalls.

  - BP_WallExplostion.

 # Enumerators blueprint.

  - EGameOverStatus.

 # Widgets bluprints.

  - WBP_GameOver.

  - WBP_PlayerStatus.

  - WBP_ScoreAndTime.
 
 # Next steps.
 
  1. Include Ambient sound and sound FX.

  2. Improve player status UI. Add a time bar to show when remote bomb is active.
  
  3. Add splines at BP_Bomb for generate the explosion visual effect or some particle system.

  4. Make the score system more robust. Pass instigator using DamageInterface, the instigator gain score points when kill enemie.
  
  5. Include AI in the game.
  
 # Spended working hours.
 Around 14h.
 ## Authors
* **Thiago C. Junqueira**




