<!--suppress HtmlDeprecatedAttribute -->
<div id="top"></div>

# Misty Engine

[![MIT License][license-shield]][license-url] <br/>
[![Stargazers][stars-shield]][stars-url] <br/>

<details open>
    <summary>Table of Contents</summary>
    <ol>
        <li>
            <a href="#about">About The Project</a>
            <ul>
                <li><a href="#concepts">Planned Concepts</a></li>
                <li><a href="#libraries">Libraries</a></li>
            </ul>
        </li>
        <li><a href="#license">License</a></li>
    </ol>
</details>


<div id="about"></div>

## About The Project

![Misty Demo](demo/Misty-Demo.gif)

Misty is a bare-bones 3D graphics engine developed by a lazy student in 3 weeks using OpenGL and many tutorials.
It serves as the final project for the Computer Graphics course, where the objective is to try creating a scene using all the taught concepts.

This engine features the following:
* Separate modules which can communicate with each other indirectly via the engine itself as a mediator;
* Singletons for classes that should only have a single instance at once;
* A basic logging system to keep track of each module's requests from the engine
* Helpful macros used for debugging or global constants
* Precompiled headers for shorter build times
* Multithreading support for more efficiency
* An FPS counter to keep track of performant (or not) the engine runs
* The ability to run on both Windows and Linux based operating systems
* No comments whatsoever (it's self-documented)

Of course, Misty is a far cry from an engine that could be used for actual projects.
This was more of a personal exercise than to make something useful and I've learnt quite a lot in the time spent developing it.

Still, feel free to take a gander at my work if you so desire, but be warned: the code could've been written _much_ better.

<p align="right">(<a href="#top">back to top</a>)</p>


<div id="concepts"></div>

### Planned Concepts

The following list contains the features that were planned to be added in Misty:
- [x] Blending
- [ ] Order-independent transparency
- [x] Right-click menu
- [ ] Free camera
- [x] Shaders
- [ ] Texturing
- [x] Keyboard input handling
- [ ] Normal bumping
- [ ] Config files
- [ ] Physics module
- [ ] Runtime creation
* Rendering
  - [x] Instances
  - [x] Text
* Lighting
  - [x] Static
  - [ ] Dynamic
* Shadows
  - [x] Static
  - [ ] Dynamic
* Loading data from files
  - [x] Shaders
  - [ ] Vertex data
* Contexts
  - [ ] Multiple VAOs
  - [x] Multiple VBOs
  - [ ] Multiple Shaders
  - [ ] Multiple Textures
  - [ ] Multiple Cameras
  - [ ] Multiple Windows
  - [ ] Multiple Menus

As you can see, many of the features above are missing, which is a shame.
However, I'm happy with how the engine turned out.
Maybe I'll come back to Misty, preferably with a team, to finish everything.
I doubt the final product could compare to the likes of Unity, Unreal or Godot.


<div id="libraries"></div>

### Libraries

Misty Engine has been built using the following libraries:

* [freeglut](https://www.transmissionzero.co.uk/software/freeglut-devel/)
* [GLEW](http://glew.sourceforge.net/)
* [SOIL](https://github.com/littlstar/soil)
* [EnTT](https://github.com/skypjack/entt)

<p align="right">(<a href="#top">back to top</a>)</p>


<div id="license"></div>

## License

Distributed under the [GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/) License.
See `LICENSE.md` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>


[license-shield]: https://img.shields.io/github/license/bUsernameIsUnavailable/Misty-Engine?style=for-the-badge
[license-url]: https://github.com/bUsernameIsUnavailable/Misty-Engine/blob/master/LICENSE.md
[stars-shield]: https://img.shields.io/github/stars/bUsernameIsUnavailable/Misty-Engine?style=for-the-badge
[stars-url]: https://github.com/bUsernameIsUnavailable/Misty-Engine/stargazers
