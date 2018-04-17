# Image Manipulation

This code demonstrates following effects:
1. Luminance effect.

![luminance](https://user-images.githubusercontent.com/7290739/38895383-ebdb73f4-425d-11e8-8e63-c0538740fee1.png)

2. Negative effect.

![negative](https://user-images.githubusercontent.com/7290739/38895374-e523d5a6-425d-11e8-802c-1f7c3dc972d3.png)

3. Edge detection.

![edge_detection](https://user-images.githubusercontent.com/7290739/38895534-4cc9ae1a-425e-11e8-9d12-3c706beb2599.png)

4. Emboss effect.

![emboss](https://user-images.githubusercontent.com/7290739/38895400-f89fe12e-425d-11e8-8c0a-a1421af4600f.png)

5. Toon shading.

![toon](https://user-images.githubusercontent.com/7290739/38895397-f5cb97e0-425d-11e8-88e5-b1c3c99d2e87.png)

6. Twirl effect.

![twirl](https://user-images.githubusercontent.com/7290739/38895402-fa86a66c-425d-11e8-9779-86f46a295c29.png)

7. Ripple effect.

![ripple](https://user-images.githubusercontent.com/7290739/38895407-fc9fb81c-425d-11e8-90fd-882eb3c93ec1.png)

8. Spherical effect.

![spherical](https://user-images.githubusercontent.com/7290739/38895415-01f172c4-425e-11e8-98ef-ddf6fe3abc3f.png)

Refer to fshader1.cpp and look for float values
mentioned in imageManipulation.cpp
Each effect performs various operations on texels and applies calculated fColor.


<pre>
Key 'O': Display original picture (usain_bolt.bmp) 
I switch all the bool toggles to false
sets effectToggle value to 0.0f in vertex shader

Key 'L': Display picture with Luminance effect (gray scale) 
bool luminance_toggle = true and the rest false
sets effectToggle value to 2.0f in vertex shader


Key 'N': Display image negative 
bool neagtive_toggle = true and the rest false
sets effectToggle value to 1.0f in vertex shader

Key 'D': Display image with edge detection effect 
bool edge_detection = true and the rest false
sets effectToggle value to 3.0f in vertex shader


Key 'E': Display image with embossing effect 
bool emboss_toggle = true and the rest false
sets effectToggle value to 4.0f in vertex shader


Key 'T': Display image with Toon rendering 
bool toon_toggle = true and the rest false
sets effectToggle value to 5.0f in vertex shader


Key 'W': Display image with Twirl Transformation 
bool twirl_toggle = true and the rest false
sets effectToggle value to 6.0f in vertex shader


Key 'P': Display image with Ripple Transformation 
bool ripple_toggle = true and the rest false
sets effectToggle value to 7.0f in vertex shader


Key 'S': Display image with Spherical Transformation 
bool spherical_toggle = true and the rest false
sets effectToggle value to 8.0f in vertex shader
</pre>
