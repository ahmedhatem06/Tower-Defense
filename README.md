# Tower-Defense
This is a tower defense game made by Unreal Engine 5.2 using C++.

Turret System:
The Turret class serves as the base for all turret types, encompassing key functionalities. Derived classes modify specific functions to customize turret behavior, such as shooting. Turret properties are stored in a data asset like damage, fire rate, etc.., ensuring modular and efficient configuration.

Turret Weapons:
The Bullets class serves as an actor that engages with an enemy by interpolating towards it.
Meanwhile, the EnergyWeapon class is the base class for all energy-based weapons. It detects and traces enemies, establishes the length of the energy beam, and various derived classes modify the effect function, determining whether to inflict damage or slow the enemy's movement.

Turret Manager:
TurretPlacement operates as a singleton, tasked with turret instantiation and managing turret selection. It transmits essential data to the Heads-Up Display (HUD) for presenting properties related to the chosen turret. In the event of an upgrade, it triggers a callback to TurretPlacement, which, in turn, invokes the Upgrade function within the Turret class.

HUD:
The HUD oversees UI management and houses various widget classes. When data is conveyed to a widget, it undergoes a two-step process: first transmitted to the HUD and subsequently forwarded to the respective widget.
The DataWidget exhibits crucial information for user awareness, encompassing details such as health, aliens eliminated, and currency. Meanwhile, the TurretsWidget showcases deployable turrets alongside their individual costs and textures.
Handling turret upgrades and sales, TurretUpgrade also reveals turret properties like damage and type. TurretPlacement facilitates the transfer of essential information to the HUD when a user clicks on a turret.

Economy:
Currency, implemented as a singleton, manages the in-game economy. It oversees the purchase and sale of turrets, as well as currency accrual when enemies are defeated.

Wave Management:
EnemiesManager, also implemented as a singleton, orchestrates the game's wave system. It manages wave progression, enemy spawning, intervals between spawns, and dynamically adjusts difficulty with each wave. When an enemy is killed, it boradcast an event within the EnemiesManager to it keeps track of the enemies alive and enemies killed in order to spawn another wave.
Enemy System:
The Enemy class is the base class for enemy entities, with specialized derived classes like Enemy_Ground and Enemy_Air for ground and air enemies, respectively. An AI controller manages enemy movement, triggering events upon reaching the base to initiate attacks. Animations are controlled by the Animation blueprint.
Enemies properties are stored in a data asset like health, speed, etc..