/**
Nexteroids - A cross platform, networked asteroids game.
Copyright (C) 2010 Jonathan Frawley

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include "nxGameScreen.hpp"

#include <nxGameApp/nxNexteroidsGameApp.hpp>
#include <nxActor/nxRockActor.hpp>

const GLfloat NX_LIGHT_POSITION[4] = { 0.0, 5.0, 10.0, 1.0 };
const GLfloat NX_WHITE_LIGHT[] = {1.0, 1.0, 1.0, 1.0};

nxGameScreen::nxGameScreen()
{
	m_RenderDebug = true;
}

nxGameScreen::~nxGameScreen()
{
}

void nxGameScreen::SetupLighting()
{
	glLightfv(GL_LIGHT0, GL_POSITION, NX_LIGHT_POSITION);
	glLightfv(GL_LIGHT0, GL_SPECULAR, NX_WHITE_LIGHT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, NX_WHITE_LIGHT);
	glLightfv(GL_LIGHT0, GL_AMBIENT, NX_WHITE_LIGHT);
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);

}

bool nxGameScreen::InitGL()
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, 0, 0, 1);
	glMatrixMode (GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);

	m_ShipList = glGenLists(1);
	glNewList(m_ShipList, GL_COMPILE);
	glScalef(20,20,20);
		glBegin(GL_LINE_LOOP);						// Drawing Using Triangles
			glVertex2f( 0.0f,  -1.0f);				// Top
			glVertex2f( -0.5f,  1.0f);				// Bottom Left
			glVertex2f( 0.5f,  1.0f);				// Bottom Right
		glEnd();
	glEndList();

}

bool nxGameScreen::Init()
{
	InitGL();

	m_Font = new FTGLPixmapFont ("../../media/font/Abduction III.ttf");

	// If something went wrong, bail out.
	if(m_Font->Error())
	{
		assert(0 && "Font is wrong");
	}

	// Set the font size and render a small text.
	m_Font->FaceSize(32);

	m_Score = 0;
}

void nxGameScreen::VOnUpdate(int deltaMilliseconds)
{

}

float ConvertYToScreen(float y)
{
	return ((float)NX_SCREEN_HEIGHT) - y;
}

void nxGameScreen::DrawBox(nxReal halfSize)
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(-halfSize, -halfSize);
		glVertex2f(halfSize, -halfSize);
		glVertex2f(halfSize, halfSize);
		glVertex2f(-halfSize, halfSize);
	glEnd();
}

void nxGameScreen::DrawPoints(vector<nxPoint3> points)
{
	glBegin(GL_POINTS);
		vector<nxPoint3>::iterator it, itEnd;
		for(it = points.begin(), itEnd = points.end() ; it != itEnd ; it++)
		{
			glVertex2f((*it).GetX(), (*it).GetY());
		}
	glEnd();
}

void nxGameScreen::VOnRenderActor(shared_ptr<nxIActor> actor)
{
	glPushMatrix();

		
	if(actor->VGetType() == NX_ACTOR_SPACESHIP)
	{

		glTranslatef(actor->VGetPos().GetX(),ConvertYToScreen(actor->VGetPos().GetY()),0);
		glRotatef( -nx_radians_to_degrees(actor->VGetOrientation() - NX_PI_OVER_2), 0,0,1);

		glColor3f(actor->VGetColour().r, actor->VGetColour().g, actor->VGetColour().b);
		glCallList(m_ShipList);
	}
	else if(actor->VGetType() == NX_ACTOR_BULLET)
	{
		glColor3f(actor->VGetColour().r, actor->VGetColour().g, actor->VGetColour().b);
		glTranslatef(actor->VGetPos().GetX(),ConvertYToScreen(actor->VGetPos().GetY()),0);

		float radius = actor->GetRadius();

		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0, 0);
			float angle = 0;
			while(angle<360)
			{
				glVertex2f(sin(angle) * radius, cos(angle) * radius);
				angle += 5.0f;
			}
		glEnd();
	}
	else if(actor->VGetType() == NX_ACTOR_ROCK)
	{	
		glColor3f(actor->VGetColour().r, actor->VGetColour().g, actor->VGetColour().b);
		glTranslatef(actor->VGetPos().GetX(), ConvertYToScreen(actor->VGetPos().GetY()),0);
		glRotatef( -nx_radians_to_degrees(actor->VGetOrientation()), 0,0,1);

		nxRockActor* castActor = (nxRockActor*)(actor.get());
		vector<nxPoint3> points = castActor->GetPoints();

		if(m_RenderDebug)
		{
			glPushMatrix();
				DrawPoints(points);
			glPopMatrix();
		}

		glBegin(GL_LINE_LOOP);
			vector<nxPoint3>::iterator it, itEnd;
			for(it = points.begin(), itEnd = points.end() ; it != itEnd ; it++)
			{
				stringstream out;
				out<<"Point.GetX() is :"<<(*it).GetX() <<","<<endl;
				out<<"Point.GetY() is :"<<(*it).GetY() <<","<<endl;
				log(NX_LOG_DEBUG, out.str());

				glVertex2f((*it).GetX(), -((*it).GetY()));
			}
		glEnd();
	}

	glPopMatrix();
}

void nxGameScreen::VOnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glLoadIdentity();

	vector<shared_ptr<nxIActor> >::iterator it, itEnd;
	for(it = m_Actors.begin(), itEnd = m_Actors.end() ; it != itEnd ; it++)
	{
		VOnRenderActor((*it));
	}

	stringstream out;
	out<<"Your score : "<<m_Score;
	m_Font->Render(out.str().c_str());

    SDL_GL_SwapBuffers( );
}
