# 42-raytracer
raytracer project from 42.

### mac
working branch for MAC systems is https://github.com/lcavalleria/42-raytracer/tree/1a20c627327aacacd12cbc15b3bca7b84630d853

get in the cloned folder and run
```bash
make
./rt [file]
```
everything should work

### windows
branch for windows is master last commit.

install ubuntu for windows 10 in microsoft store

install xming

open ubuntu terminal and run

```bash
apt-get install sdl2-dev
apt-get install sdl2-ttf-dev
   ```             
then clone the repo in ubuntu, get in, and run
```bash
make
./rt [file]
```



files are in scenes folder

## features
when we execute the raytracer, we will see this. the low res image is so to be able to control the scene in real time.

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/low%20res%20sphere.png" width="640"/>
</p>
Once we hit enter we will see the image properly rendered.
<br/><br/><br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/sphere.png" width="640"/>
</p>
So far we have only seen the sphere, but there is more shapes we can render.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/quadratics.png" width="640"/>
</p>
We can also render more complex shapes with 4 possible intersection points.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/quartics.png" width="640"/>
</p>
And we can parse a .obj file and render it as triangles.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/mesh.png" width="640"/>
</p>
There is an option to generate objects in the scene from a pattern.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/adn.png" width="640"/>
</p>
Or we can clone groups of custom objects.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/defines.png" width="640"/>
</p>
The lights can have any color and they will interact properly with the world and with each other.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/colored%20lights.png" width="640"/>
</p>
Objects can have a transparency and a refraction index.
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/refraction.png" width="640"/>
</p>
They can also have a reflection index (0, no reflection to 1, perfect mirror).
<br/>

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/reflection.png" width="640"/>
</p>
Objects color and normal vectors can be altered depending on the hitpoint position.
<br/>

<table>
<td><p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/waves.png" width="320"/>
   </p></td>
<td><p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/ripple.png" width="320"/>
   </p></td>
<td><p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/noise.png" width="320"/>
   </p></td>
   </table>
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/chess.png" width="320"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/perlin.png" width="320"/>
</p>
note that the colors perturbations will depend on the object's color at a specific point, even if it comes form a texture.

----------------------------------------------------
cuts
negatius
textures
textures chachis
disco
bump mapping
fog
antialiasing
filters
cartoon


<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/kirbydemo.gif" width="640"/>
</p>
