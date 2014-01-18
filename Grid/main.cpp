#include <iostream>
#include <Windows.h>
#include "include\glut.h"
#include "include\map.h"
#include <fstream>
int match1;
int match2;
int coord_x = 30;
int coord_y = 30;
int angle = 0;
int currentColor = 0;
bool motionStart = false;
bool showgrid = true;
bool map_select = 0;
int ff = 0;
Map m = Map(map1);
Map m2 = Map(map2);
Teleport t1 = Teleport(5,5,20,20);
Teleport t2 = Teleport(9,9,13,15);

//ИЛИ: ||
//И: &&
//НЕ: !
///////



void drawgrid(bool gridflag);

void keyboard(unsigned char key, int x, int y)
{
	Map* curr = NULL;
	if(map_select == 0)
	{ 
		curr = &m;
	}
	else
	{
		curr = &m2;
	}

	int index1 = coord_x / curr->size - 1;
	int index2 = coord_y / curr->size - 1;
	switch(key)
	{
	case 'd':
		if ( (coord_x + curr->size) < 620 && curr->values[index2][index1+1] != 1 )
		{
			for(int i=0; i < curr->t_count; i++)
			{
				if(curr->t(i)->posX == index1 && curr->t(i)->posY == index2)
				{
					coord_x = curr->t(i)->targetX * curr->size + 10;
					coord_y = curr->t(i)->targetY * curr->size + 10;
					break;
				}
			}
			
			if(curr->values[index2][index1+1] == 4)
			{
				map_select = !map_select;
				coord_x = 30;
				coord_y = 30;
			}
			else
			{
				coord_x += m.size;
				coord_y += 0;
			}
		}
		break;
		
	case 'a':
		if ( (coord_x - curr->size) > 20 && curr->values[index2][index1-1] !=1 )
		{	
			for(int i=0; i < curr->t_count; i++)
			{
				if(curr->t(i)->posX == index1 && curr->t(i)->posY == index2)
				{
					coord_x = curr->t(i)->targetX * curr->size + 10;
					coord_y = curr->t(i)->targetY * curr->size + 10;
					break;
				}
			}

			if(curr->values[index2][index1-1] == 4)
			{
				map_select = !map_select;
				coord_x = 30;
				coord_y = 30;
			}
			else
			{
				coord_x -= curr->size;
			}
		}
		break;
		 
	case 'w':

		if ((coord_y + curr->size) < 460 && curr->values[index2+1][index1]!=1)
		{
			for(int i=0; i < curr->t_count; i++)
			{
				if(curr->t(i)->posX == index1 && curr->t(i)->posY == index2)
				{
					coord_x = curr->t(i)->targetX * curr->size + 10;
					coord_y = curr->t(i)->targetY * curr->size + 10;
					break;
				}
			}

			if((curr->values[index2+1][index1] == 4))
			{
				map_select = !map_select;
				coord_x = 30;
				coord_y = 30;
			}
			else
			{
				coord_y += curr->size;
			}
		}
		break; 
		

	case 's':
		if ( (coord_y - curr->size) > 20 && curr->values[index2-1][index1] != 1)
		{
			for(int i=0; i < curr->t_count; i++)
			{
				if(curr->t(i)->posX == index1 && curr->t(i)->posY == index2)
				{
					coord_x = curr->t(i)->targetX * curr->size + 10;
					coord_y = curr->t(i)->targetY * curr->size + 10;
					break;
				}
			}

			if(curr->values[index2-1][index1] == 4)
			{
				map_select = !map_select;
				coord_x = 30;
				coord_y = 30;
			}
			else 
			{
				coord_y -= curr->size;
			}
		}
		break;

	case 'h':
		showgrid = !showgrid;
		break;
	case 'r':
		coord_x = 30;
		coord_y = 30;
		break;
	
	case '1':
		ff++;
		break;

	case '2':
		ff--;
		break;
	
	default:
		break;
	
	}
	glutPostRedisplay();
}
void display()
{
	glViewport(0,0,640,480);
	double aspect = 3.0/4;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,640,0,480,-100,100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);

	Map* current = NULL;
	if(map_select == 0)
	{
		current = &m;
	}
	else
	{
		current = &m2;
	}

	glBegin(GL_QUADS);
	for (int i=0; i<m.y-2; i++)
		for(int j=0; j<m.x-2; j++)
		{
			if (current->values[i][j] == 0) 
			{ 
				 continue; 
			}

			else if(current->values[i][j] == 2)
			{
				glColor3f(1,0,0);
			}
			else if (current->values[i][j] == 1)
			{
				glColor3ub(160,255,0);
			}
			else if (current->values[i][j] == 3)
			{
				glColor3f(0,0,1);
			}
			else if (current->values[i][j] == 4)
			{
				glColor3f(1,0,1);
			}
			double size = current->size;
			glVertex2d((j+2)*size, (i+2)*size);
			glVertex2d((j+2)*size, (i+1)*size);
			glVertex2d((j+1)*size, (i+1)*size);
			glVertex2d((j+1)*size, (i+2)*size);
									  
		}
	glEnd();
	
	glColor3d(1,0,0);
	glPushMatrix();
	glTranslated(coord_x,coord_y,0);
	glRotated(angle,0,0,1);
	glutSolidCube(20);
	glPopMatrix();

	
	drawgrid(showgrid);
	

	glFlush();
}
void switchColor(int num)
{
	currentColor = num;
}
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		motionStart = true;
		int index1 = x / m.size - 1;
		int index2 = y / m.size - 1;
		if(index1>=0 && index1 < m.y-2 && index2 < m.x-2 && index2>=0) m.values[index1][index2] = currentColor;
	}
	else
	{
		motionStart = false;
	}
	glutPostRedisplay();
}
void motion(int x, int y)
{
	if(motionStart)
	{
		int index1 = x / m.size - 1;
		int index2 = y / m.size - 1;
		if(index1>=0 && index1 < m.y-2 && index2 < m.x-2 && index2>=0) m.values[index1][index2] = currentColor;
		std::cout << index1 << " " << index2 << std::endl;
	}
	glutPostRedisplay();
}
/*void createFile()
{
	CreateDirectory("files", NULL);
	char fileName[] = "files/test123.mp";
	FILE *f = fopen(fileName,"w");
	if(f != NULL)
	{
		fputs("testContent",f);
		fclose(f);
	}
}*/

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "RUS");
	std::cout << "Управление:" << std::endl;
	std::cout << "Правая кномка мыши - выбор цвета" << std::endl;
	std::cout << "Левая кнопка мыши - рисование " << std::endl;
	
	std::cout << getenv("PATH") << std::endl;
	//createFile();

	system("Pause");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(300,200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Game.exe");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutCreateMenu(switchColor);
	glutAddMenuEntry("Красный", 1);
	glutAddMenuEntry("Желтый", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	m = Map(map1);
	m.add_teleport(t1);
	
	m2 = Map(map2);
	m2.add_teleport(t2);

	glutMainLoop();
	return 0;
}

void drawgrid(bool gridflag)
{
	if (!gridflag) return;
	
	glColor3ub(32+ff,32+ff,32+ff);
	glBegin(GL_LINES);
	for(int i=1; i < m.x; i++)
	{
		glVertex2d(i*m.size, 20);
		glVertex2d(i*m.size, 460);
	}

	for(int i=1; i < m.y; i++)
	{
		glVertex2d(20, i*m.size);
		glVertex2d(620, i*m.size);
	}

	glEnd();
}
