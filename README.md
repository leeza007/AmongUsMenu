# AmongUsMenu

<p align="center">
   AmongUsMenu is a Cheat Menu for the popular Game Among Us.
</p>

## Disclaimer
This project is for Educational Use only. We do not condone this software being used to gain an advantage against other people. I made this project for my university project to show how cheating software works and how it is possible to block these manipulations in the future.

## Compile (Configurations)
You can compile two different versions of the menu. Normal or Xinput.

### Normal (AmongUsMenu.dll)
Inject it with any injector you have. The ``resources`` folder needs to be in the same path as the dll.

- Debug (With Debug Information and can be attached to process)
- Release (Optimized with all information stripped)

### Xinput (xinput1_3.dll)
Will automatically be loaded by the Game itself if the dll is in the game directory. Make sure to include the ``resources`` folder into the same path as the game directory too.

- Debug_Xinput (With Debug Information and can be attached to process)
- Release_Xinput (Optimized with all information stripped)

### Default Hotkeys
- Show Menu - DELETE
- Show Radar - INSERT
- Show Console - HOME
- Repair Sabotage - END

## Screenshot
<p align="center">
   <img src="screenshot.png">
</p>

## Credits
* [void*](https://github.com/v0idp) (Creator)
* [std-nullptr](https://github.com/std-nullptr) (Contributor & Il2cpp Madman)
* [OsOmE1](https://github.com/OsOmE1) (Contributor)
* [RealMVC](https://github.com/RealMVC) (Contributor)

## Contributing

1. Fork it (<https://github.com/v0idp/AmongUsMenu/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
