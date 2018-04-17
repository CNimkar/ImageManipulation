//
// Display a Mandelbrot set
//

// Uncomment the following line to use user-specified input values
// #define USER_INPUT

#ifdef USER_INPUT
// Include the C++ iostreams classes for use when collecting user input
#include <iostream>
#endif 

#include "Angel.h"
#include "bmpread.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

// Use the C++ standard complex-number class.  It's a C++ template, so
//   we create a typedef of simplify our code.
#include <complex>
typedef std::complex<float>  Complex;

inline float Random() { return float(rand())/RAND_MAX; }

GLuint Projection;

/* default data*/
/* can enter other values via command line arguments */

#define CENTERX -0.5
#define CENTERY 0.5
#define HEIGHT 0.5
#define WIDTH 0.5
#define MAX_ITER 100

/* N x M array to be generated */

#define N 512
#define M 512

float height = HEIGHT;          /* size of window in complex plane */
float width = WIDTH;


int n = N;
int m = M;


bmpread_t bitmap;

static  GLuint  texture = 0;
GLuint program;
bool neagtive_toggle = false;
bool luminance_toggle = false;
bool edge_detection = false;
bool emboss_toggle = false;
bool toon_toggle = false;
bool twirl_toggle = false;
bool ripple_toggle = false;
bool spherical_toggle = false;

//----------------------------------------------------------------------------

void
init( void )
{
	printf("Loading usain_bolt.bmp\n");

	if(!bmpread("usain_bolt.bmp", 0, &bitmap))
	{
		fprintf(stderr, "%s:error loading bitmap file\n", "usain_bolt.bmp");
		exit(1);
	}

    glActiveTexture( GL_TEXTURE0 );
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap.rgb_data );
	bmpread_free(&bitmap);


    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    point4 points[6] = {
	point4( 0.0, 0.0, 0.0, 1.0 ),
	point4( 0.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 0.0, 0.0, 1.0 ),
	point4( 0.0, 0.0, 0.0, 1.0 )
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader1.glsl", "fshader1.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    // Since our texture coordinates match our vertex positions, we
    //   can reuse the position data for our texture coordinates.
    GLuint vTexCoord = glGetAttribLocation( program, "vTexCoord" ); 
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer( vTexCoord, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    Projection = glGetUniformLocation( program, "Projection" );

    // Set our texture samples to the active texture unit
    glUniform1i( glGetUniformLocation(program, "texture"), 0 );
    glBindTexture(GL_TEXTURE_2D, texture);

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    mat4 projection = Ortho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );

}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
	case'n': case 'N':
		neagtive_toggle = !neagtive_toggle;
		luminance_toggle = false;
		edge_detection = false;
		emboss_toggle = false;
		toon_toggle = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case'l': case 'L':
		luminance_toggle = !luminance_toggle;
		neagtive_toggle = false;
		edge_detection = false;
		emboss_toggle = false;
		toon_toggle = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case'd': case 'D':
		edge_detection = !edge_detection;
		neagtive_toggle = false;
		luminance_toggle = false;
		emboss_toggle = false;
		toon_toggle = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case'e': case 'E':
		emboss_toggle = !emboss_toggle;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		toon_toggle = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case't': case 'T':
		toon_toggle = !toon_toggle;
		emboss_toggle = false;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case'w': case 'W':
		twirl_toggle = !twirl_toggle;
		emboss_toggle = false;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		toon_toggle = false;
		ripple_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case'p': case 'P':
		ripple_toggle = !ripple_toggle;
		twirl_toggle = false;
		emboss_toggle = false;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		toon_toggle = false;
		spherical_toggle = false;
		glutPostRedisplay();
		break;
	case's': case 'S':
		spherical_toggle = !spherical_toggle;
		ripple_toggle = false;
		twirl_toggle = false;
		emboss_toggle = false;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		toon_toggle = false;
		glutPostRedisplay();
		break;
	case'o': case 'O':
		spherical_toggle = false;
		ripple_toggle = false;
		twirl_toggle = false;
		emboss_toggle = false;
		neagtive_toggle = false;
		luminance_toggle = false;
		edge_detection = false;
		toon_toggle = false;
		glutPostRedisplay();
		break;
    }
}

//----------------------------------------------------------------------------

void
display()
{
    glClear( GL_COLOR_BUFFER_BIT );
	GLuint effect_toggle_info = glGetUniformLocation(program, "effectToggle");
	if (neagtive_toggle)
		glUniform1f(effect_toggle_info, 1.0f);
	else if(luminance_toggle)
		glUniform1f(effect_toggle_info, 2.0f);
	else if (edge_detection)
		glUniform1f(effect_toggle_info, 3.0f);
	else if (emboss_toggle)
		glUniform1f(effect_toggle_info, 4.0f);
	else if (toon_toggle)
		glUniform1f(effect_toggle_info, 5.0f);
	else if (twirl_toggle)
		glUniform1f(effect_toggle_info, 6.0f);
	else if (ripple_toggle)
		glUniform1f(effect_toggle_info, 7.0f);
	else if (spherical_toggle)
		glUniform1f(effect_toggle_info, 8.0f);
	else
		glUniform1f(effect_toggle_info, 0.0f);
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( N, M );
    glutInitContextVersion( 3, 3 );
//    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Image Manipulation" );

	glewExperimental = GL_TRUE;

    glewInit();

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
