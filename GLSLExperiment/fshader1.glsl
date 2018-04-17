#version 150

in  vec2 texCoord;
out vec4 fColor;
uniform float effectToggle;

uniform sampler2D texture;

void main() 
{ 
	if(effectToggle == 0.0f){
		fColor = texture2D( texture, texCoord );
	}

	else if(effectToggle == 1.0f){
		fColor = texture2D( texture, texCoord );
		fColor = vec4(1-fColor.x, 1-fColor.y, 1-fColor.z, 1.0);
	}

	else if(effectToggle == 2.0f){
		const vec3 W = vec3(0.2125, 0.7154, 0.0721);
		fColor = texture2D( texture, texCoord );
		vec3 irgb = fColor.rgb;
		float luminance = dot(irgb, W);
		fColor = vec4(luminance, luminance, luminance, 1.0);
	}

	else if(effectToggle == 3.0f){

	vec3 LUMCOEFFS =  vec3(0.2125, 0.7154, 0.0721);

	ivec2 ires = textureSize( texture, 0);
	float ResS = float( ires.s );
	float ResT = float( ires.t );
	fColor = texture2D( texture, texCoord );
	vec3 irgb = fColor.rgb;

	vec2 stp0 = vec2(1./ResS, 0. ); //texel offsets
	vec2 st0p = vec2(0.  , 1./ResT);
	vec2 stpp = vec2(1./ResS, 1./ResT);
	vec2 stpm = vec2(1./ResS, -1./ResT);

	float i00 =	dot(texture2D( texture, texCoord ).rgb,LUMCOEFFS);
	float im1m1 = dot(texture2D( texture, texCoord-stpp ).rgb,LUMCOEFFS);
	float ip1p1 = dot(texture2D( texture, texCoord+stpp ).rgb,LUMCOEFFS);
	float im1p1 = dot(texture2D( texture, texCoord-stpm ).rgb,LUMCOEFFS);
	float ip1m1 = dot(texture2D( texture, texCoord+stpm ).rgb,LUMCOEFFS);
	float im10 = dot(texture2D( texture, texCoord-stp0 ).rgb,LUMCOEFFS);
	float ip10 = dot(texture2D( texture, texCoord+stp0 ).rgb,LUMCOEFFS);
	float i0m1 = dot(texture2D( texture, texCoord-st0p ).rgb,LUMCOEFFS); 
	float i0p1 = dot(texture2D( texture, texCoord+st0p ).rgb,LUMCOEFFS);

	float h = -1*im1p1 - 2*i0p1 -1*ip1p1 +1*im1m1 + 2*i0m1 + 1*ip1m1;
	float v = -1*im1m1 - 2*im10 -1*im1p1 +1*ip1m1 + 2*ip10 + 1*ip1p1;

	float mag   = length( vec2( h, v ) );
	vec3 target = vec3(mag, mag, mag);
	fColor= vec4(mix(irgb, target, texCoord.t ), 1.);
}

else if(effectToggle == 4.0f){
	ivec2 ires = textureSize( texture, 0);
	float ResS  = float( ires.s );
	float ResT  = float( ires.t );
	vec3 irgb  = texture2D( texture, texCoord ).rgb;
	vec2 stp0  = vec2(1./ResS, 0. );
	vec2 stpp  = vec2(1./ResS, 1./ResT);
	vec3 c00   = texture2D( texture, texCoord ).rgb;
	vec3 cp1p1 = texture2D( texture, texCoord + stpp ).rgb;
 	vec3 diffs = c00 - cp1p1; // vector difference
 	float max = diffs.r;
 	if ( abs(diffs.g) > abs(max) ) max = diffs.g;
 	if ( abs(diffs.b) > abs(max) ) max = diffs.b;
 	float gray = clamp( max + .5, 0., 1. );
 	vec3 color = vec3( gray, gray, gray );
 	fColor = vec4( color, 1. );
 }

 else if(effectToggle == 5.0f){
	ivec2 ires = textureSize( texture, 0 );
 	float ResS = float( ires.s );
 	float ResT = float( ires.t );
 	vec3 irgb = texture2D( texture, texCoord ).rgb;
 	vec3 brgb = texture2D( texture, texCoord ).rgb;
 	vec3 argb = texture2D( texture, texCoord ).rgb;
 	vec3 rgb = texture2D( texture, texCoord ).rgb;
 	vec2 stp0 = vec2(1./ResS, 0. );
 	vec2 st0p = vec2(0.   , 1./ResT);
 	vec2 stpp = vec2(1./ResS, 1./ResT);
 	vec2 stpm = vec2(1./ResS, -1./ResT);
 	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
 	float i00 =  dot( texture2D( texture, texCoord).rgb, W );
 	float im1m1 = dot( texture2D( texture, texCoord-stpp ).rgb, W );
 	float ip1p1 = dot( texture2D( texture, texCoord+stpp ).rgb, W );
 	float im1p1 = dot( texture2D( texture, texCoord-stpm ).rgb, W );
 	float ip1m1 = dot( texture2D( texture, texCoord+stpm ).rgb, W );
 	float im10 =  dot( texture2D( texture, texCoord-stp0 ).rgb, W );
 	float ip10 =  dot( texture2D( texture, texCoord+stp0 ).rgb, W );
 	float i0m1 =  dot( texture2D( texture, texCoord-st0p ).rgb, W );
 	float i0p1 =  dot( texture2D( texture, texCoord+st0p ).rgb, W );
	 // next two lines apply the H and V Sobel filters at the pixel
 	float h= -1.*im1p1-2.*i0p1-1.*ip1p1+1.*im1m1+2.*i0m1+1.*ip1m1;
 	float v= -1.*im1m1-2.*im10-1.*im1p1+1.*ip1m1+2.*ip10+1.*ip1p1;
	 float mag = length( vec2( h, v ) );
	 if( mag > 2.0 )
	 { // if too much, use black
	 	fColor = vec4( 0., 0., 0., 1. );
	 }
	 else
	 {        // else quantize the color
	 	rgb.rgb *= 2.2;
	  rgb.rgb += vec3( .5, .5, .5 );   // round
	  ivec3 intrgb = ivec3( rgb.rgb );  // truncate
	  rgb.rgb = vec3( intrgb ) / 3.0;
	  fColor = vec4( rgb, 1. );
	}

}

else if(effectToggle == 6.0f){
	ivec2 ires = textureSize( texture, 0 );
	 float Res = float( ires.s ); // assuming it’s a square 
	 vec2 st = texCoord;
	 float Radius = Res * 0.5;
	 vec2 xy = Res * st;     // pixel coordinates from texture coordinates
	 vec2 dxy = xy - Res/2.; // twirl center is (Res/2, Res/2)  
	 float r  = length( dxy );
	 float beta = atan(dxy.y,dxy.x) + radians(45.0f)*
	 (Radius-r)/Radius;
	 vec2 xy1 = xy;
	 if (r <= Radius)
	 {
	 	xy1 = Res/2. + r * vec2( cos(beta), sin(beta) );
	 }
	 st = xy1/Res;  // restore coordinates
	 vec3 irgb = texture2D( texture, st ).rgb;
	 fColor = vec4( irgb, 1. );
	}

	else if(effectToggle == 7.0f){

		float pi = 3.141592;

		vec2 st = texCoord;
		float Res = 200.0;
		vec2 xy = Res * st;

		xy.x = xy.x + 10*sin(2* pi * xy.y /120);
		xy.y = xy.y + 15*sin(2* pi * xy.x /250);

		st = xy/Res;
		vec3 irgb = texture2D(texture, st).rgb;
		fColor = vec4(irgb, 1.0);
	}

	else if(effectToggle == 8.0f){

	ivec2 ires = textureSize(texture, 0);
	float Res = float( ires.s ); 

	vec2 st = texCoord;
	float Radius = Res * 0.5;
	vec2 xy = Res * st;// pixel coordinates

	float dx = xy.x - Res/2.0;
	float dy = xy.y - Res/2.0;

	float r = sqrt(pow(dx,2.0) + pow(dy,2.0));
	float z = sqrt(pow(Radius,2.0) - pow(r,2.0) );

	float bxden = sqrt(pow(dx,2.0) + pow(z,2.0));
	float byden = sqrt(pow(dy,2.0) + pow(z,2.0));

	float bx = 0.44 * asin(dx/bxden);
	float by = 0.44 * asin(dy/byden);

	 vec2 xycoord = Res * st;

	 if(r <= Radius){
	 	xycoord.x -= z * tan(bx);
	 	xycoord.y -= z * tan(by);
	 }

	 st = xycoord/Res;
	 vec3 irgb = texture2D(texture, st).rgb;
	 fColor = vec4(irgb, 1.0);
	}
}