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

<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/waves.png" width="320"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/ripple.png" width="320"/>
</p>
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/noise.png" width="320"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/chess.png" width="320"/>
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/perlin.png" width="420"/>
</p>
Note that the colors perturbations will depend on the object's color at a specific point, even if it comes form a texture.

<br/>
We can "cut" objects to stop rendering them after an axis, relative or absolute. the objects will appear hollow.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/cuts.png" width="640"/>
</p>
<br/>
Or we can add negative shapes to an object, which will not render the parts inside this negatve object, and will make the object look full.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/negatives.png" width="640"/>
</p>
of course, reflections and refractions still apply to objects with negatives.

<br/>
<br/>
Texture can be applied to objects.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/textures.png" width="640"/>
</p>
And they can be set to act as a transparency/reflection/refraction modifier using a certain color as a code (blue for example).
<br/>
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/worldglass.png" width="640"/>
</p>
<br/>
Or they can be set to not render anything. In the following image, it is not rendering the sea as transparent, it's simply not rendering it at all.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/texturecut.png" width="640"/>
</p>
<br/>
The light that goes through textures of transparent objects will project colored light properly just like with plain color.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/texture_transp.png" width="640"/>
</p>

<br/>
Textures don't only have to be for colors, they can also be used for normal vectors (aka bump mapping).
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/bumpmapping.png" width="640"/>
</p>
this is not an object with negatives, it's a simple sphere. in fact, if we get closer, we will see that where there is no light, it looks completely plain as expected.
we can "cut" objects to stop rendering them after an axis, relative or absolute. the objects will appear hollow.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/bumpclose.png" width="640"/>
</p>
<br/>

There is an option to render fog.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/fog.png" width="640"/>
</p>
<br/>

We can set the antialiasing for better quality. it will render a square of nxn pixels for each pixel and get the mean color.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/noantialiasing.png" width="420"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/antialiasing.png" width="420"/>   
</p>
<br/>

There is some filters we can apply to the final image: Gauss blur, motion blur, emboss, sharpen edges, sobel, greyscale.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/gaussblur.png" width="420"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/motionblur.png" width="420"/>   
</p>
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/emboss.png" width="420"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/sharpen.png" width="420"/>   
</p><p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/grey.png" width="420"/>
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/sobel.png" width="420"/>   
</p>
<br/>
And there is an option to render with cartoon shaders instead of realistic. It will paint the edges black using the sobel filter.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/cartoon.png" width="640"/>
</p>
<br/>

This is an example of a scene that uses some of the features at the same time.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/example.png" width="640"/>
</p>
<br/>

And this is what editing a scene in real time looks like.
<p align="center">
<img src="https://github.com/lcavalleria/42-raytracer/blob/master/captures/kirbydemo.gif" width="640"/>
</p>
<br/>
The hotkeys for editing scene are: left click to select a group of items, shift + left click to select a specific item for a group(or use the interface list of objects), "w""a""s""d" to move the camera like a fps game, "space" to move up, "ctrl" to go down, arrow keys to change the looking direction of the camera, "shift" to do whatever action faster, "7""8", "4""5", "1""2" in the numpad to move the object on the different axis, "o", "p" to scale an object, "z""x""c""v" to rotate on different axcis (relative to the object, so rotating in one axis gives acces to the 3d axis)
