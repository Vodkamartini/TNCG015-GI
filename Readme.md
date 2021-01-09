# Monte Carlo Raytracer for TNCG-015

## Features

* Polygonial- and implicit objects, respectively.*
* Shadow ray support has been added for 'direct' shading.
* Perfect reflectors

\**(Currently presets only exist for tetrahedrons as well as spheres, respectively.)*
## Changelog

### "2021-01-06: Shadow ray were added!"

![Shadow rays introduced](Output/CurrentState.png)

### "2021-01-09: Added perfect reflectors (sphere and left wall)"

![Perfect reflectors introduced](Output/PerfectReflectors.png)
![Perfect reflectors introduced, now without wall mirror](Output/PerfectReflectors2.png)

In the second image, the color at each ray-intersection is blended between the surface color and the color of the reflected ray. Shadow rays were also calculated at each ray-intersection spawned in the ray-tree.
