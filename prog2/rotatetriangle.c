#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat triangle[3][3] = {{200.0,275.0,350.0},{200.0,350.0,200.0},{1.0,1.0,1.0}};
GLfloat rot_mat[3][3] = {{0},{0},{0}};
GLfloat result[3][3] = {{0},{0},{0}};
GLfloat h = 200.0;
GLfloat k = 200.0;
GLfloat theta;

void multiply()
{
	int i,j,l;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			result[i][j] = 0;
			for(l=0;l<3;l++)
				result[i][j] = result[i][j]+rot_mat[i][l]*triangle[l][j];
		}
}

void rotate()
{
	GLfloat m,n;
	m = -h*(cos(theta)-1)+k*(sin(theta));
	n = -k*(cos(theta)-1)-h*(sin(theta));
	rot_mat[0][0]=cos(theta);
	rot_mat[0][1]=-sin(theta);
	rot_mat[0][2]=m;
	rot_mat[1][0]=sin(theta);
	rot_mat[1][1]=cos(theta);
	rot_mat[1][2]=n;
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;
	multiply();
}

void drawtriangle()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(triangle[0][0],triangle[1][0]);
	glVertex2f(triangle[0][1],triangle[1][1]);
	glVertex2f(triangle[0][2],triangle[1][2]);
	glEnd();
}

void drawrotatedtriangle()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(result[0][0],result[1][0]);
	glVertex2f(result[0][1],result[1][1]);
	glVertex2f(result[0][2],result[1][2]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawtriangle();
	rotate();
	drawrotatedtriangle();
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

void main(int argc,char **argv)
{
	printf("Enter the Rotation angle \n");
	scanf("%f",&theta);
	theta = (theta*3.1459)/180;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Triangle Rotation");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}	
