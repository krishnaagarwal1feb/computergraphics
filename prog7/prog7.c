#include<stdio.h>
#include<GL/glut.h>
float v[4][3] = { {0.0, 0.0, 1.0}, {0, 1, -1}, {-0.8, -0.4, -1}, {0.8, -0.4, -1} };
int n; // number of recursive steps.

void triangle(float a[], float b[], float c[]) // display one triangle
{
	glBegin(GL_POLYGON); // glBegin accepts a single argument that specifies in which of ten possible ways the following vertices are interpreted. Here GL_POLYGON is used to draw a single, convex 				polygon. Vertices 1 through N define this polygon.
	
	glVertex3fv(a); // glVertex specifies a vertex. The parameter to this function specifies a pointer to an array of two, three, or four elements.
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd(); 
}

void divide_triangle(float a[], float b[], float c[], int m) // divide triangle using vertex coordinates
{
	float v1[3], v2[3], v3[3]; // midpoints of each edge.
	int i;
	if(m>0)
	{
		for(i=0; i<3; i++) v1[i] = (a[i] + b[i]) / 2; // single for loop can be used instead.
		for(i=0; i<3; i++) v2[i] = (a[i] + c[i]) / 2;
		for(i=0; i<3; i++) v3[i] = (b[i] + c[i]) / 2; 
		divide_triangle(a, v1, v2, m-1);
		divide_triangle(c, v2, v3, m-1);
		divide_triangle(b, v3, v1, m-1);
	}
	else (triangle(a, b, c)); // draw triangle at end of recursion
}

void tetrahedron(int m)
{
	glColor3f(1.0, 0.0, 0.0); // glColor sets the current color. Paramters are the RGB values.
	divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0.0, 1.0, 0.0);
	divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[0], v[3], v[1], m);
	glColor3f(1.0, 1.0, 0.0);
	divide_triangle(v[0], v[2], v[3], m);
}

void display()
{
	glMatrixMode(GL_PROJECTION); // glMatrixMode specifies which matrix is the current matrix. GL_PROJECTION  applies subsequent matrix operations to the projection matrix stack. 
	glLoadIdentity(); // replaces the current matrix with the identity matrix.
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0); // glOrtho multiplies the current matrix with an orthographic matrix.
	glMatrixMode(GL_MODELVIEW); //GL_MODELVIEW applies subsequent matrix operations to the modelview matrix stack.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear clears buffers to preset values.
	tetrahedron(n);
	glFlush(); // glFlush forces execution of GL commands in finite time.
	glutPostRedisplay(); // glutPostRedisplay marks the current window as needing to be redisplayed. 
}

int main(int argc, char* argv[]) // argc - argument count of the arguments that are passed by the user.  argv - argument vector, a pointer to the array of the arguments that are passed by the user. Both 					    these are used for user input.
{
	printf("Enter the number of divisions: ");
	scanf("%d", &n);
	glutInit(&argc, argv); // glutInit is used to initialize the GLUT library. 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D Gasket");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST); // glEnable enables or disables server-side GL capabilities.
	glClearColor(1.0, 1.0, 1.0, 1.0); // glClearColor specifies clear values for the color buffers.
	glutMainLoop(); // glutMainLoop enters the GLUT event processing loop. 
	return 0;
}	
