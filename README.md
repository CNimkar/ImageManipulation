# ImageManipulation

This code demonstrates following effects:
1. Luminance effect.
2. Negative effect.
3. Edge detection.
4. Emboss effect.
5. Toon shading.
6. Twirl effect.
7. Ripple effect.
8. Spherical effect.

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
