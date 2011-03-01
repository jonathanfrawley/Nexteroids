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
#ifndef  NXROCKACTOR_H
#define  NXROCKACTOR_H

#include <stdint.h> 

#include <vector>

#include <nxCore/nxCore.hpp>
#include <nxCore/nxMath.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxActor/nxBaseActor.hpp>
#include <nxGeom/nxPoint3.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxRockActor
 *  Description: Rock actor type
 * =====================================================================================
 */
class nxRockActor : public nxBaseActor
{
	public:

		nxRockActor();

		nxRockActor(nxReal yrot, nxPoint3 pos, float radius, float speed);

		nxRockActor(const nxRockActor& other)
			:
				nxBaseActor(other)
		{
			m_Radius = other.GetRadius();
			m_Colour = other.VGetColour();
			vector<nxPoint3>::iterator it, itEnd;
			for(it = other.GetPoints().begin(), 
					itEnd = other.GetPoints().end() ; 
					it != itEnd ; 
					it++)
			{
				m_Points.push_back(*it);
			}
			m_Speed = other.VGetSpeed();
			m_RockType = other.VGetRockType();
		}

		virtual ~nxRockActor();

		virtual void VInit(stringstream& in)
		{
			nxBaseActor::VInit(in);

			in >> m_Radius;

			in >> m_Colour.r;
			in >> m_Colour.g;
			in >> m_Colour.b;
			in >> m_Colour.alpha;

			in >> m_Speed;

			uint32_t rockTypeInt;
			in >> rockTypeInt;
			m_RockType = rockTypeInt;

			uint32_t nPoints;
			in >> nPoints;
			
			for(int i = 0 ; i < nPoints ; i++)
			{
				nxPoint3 p;
				p.VInit(in);
				m_Points.push_back(p);
			}
		}

		virtual void VSerialize(stringstream& out)
		{
			nxBaseActor::VSerialize(out);

			uint32_t rockTypeInt= m_RockType;

			uint32_t pointsSizeInt = m_Points.size();
			
			for(int i = 0 ; i < m_Points.size() ; i++)
			{
				m_Points[i].VSerialize(out);
			}
		}

		virtual nxRockActor* VClone()
		{
			nxRockActor* result = new nxRockActor(m_Orientation, m_Pos, m_Radius, m_Speed);
			result->VSetColour(m_Colour);
			result->VSetSpeed(m_Speed);
			result->VSetPoints(m_Points);
			result->VSetRockType(m_RockType);

			result->VSetViewId(m_ViewId);
			result->VSetId(m_Id);
			return result;
		}

		virtual void VOnUpdate(int deltaMilliseconds)
		{
		}

		virtual void VCreate();

		virtual void VSetRadius(float val)
		{
			m_Radius = val;
		}

		virtual nxReal GetRadius() const
		{
			return m_Radius;
		}

		virtual void VSetColour(nxColour colour)
		{
			m_Colour = colour;
		}

		virtual nxColour VGetColour() const
		{
			return m_Colour;
		}

		virtual float VGetSpeed() const
		{
			return m_Speed;
		}

		virtual void VSetSpeed(float val)
		{
			m_Speed = val;
		}

		vector<nxPoint3> GetPoints() const
		{
			return m_Points;
		}

		void VSetPoints(const vector<nxPoint3>& val)
		{
			m_Points = val;
		}

		void VSetRockType(int type)
		{
			m_RockType = type;
		}

		int VGetRockType() const
		{
			return m_RockType;
		}
		
	protected:
		nxReal m_Radius;
		nxColour m_Colour;
		float m_Speed;
		vector<nxPoint3> m_Points;
		int m_RockType;
	private:
};

#endif   // NXROCKACTOR_H
