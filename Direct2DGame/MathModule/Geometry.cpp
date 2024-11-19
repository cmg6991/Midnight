#include "MathModulePCH.h"
#include "Geometry.h"

Vector2 Geometry::GetSupportingPoint ( const Vector2& _direct , const std::vector<Vector2>& _vertex )
{
	float bestProjection = -FLT_MAX;
	Vector2 bestVertex;

	for ( int i = 0; i < static_cast< int >( _vertex.size ( ) ); ++i )
	{
		Vector2 v = _vertex[i];
		float prjection = v.Dot ( _direct );
		
		if ( prjection > bestProjection )
		{
			bestVertex = v;
			bestProjection = prjection;
		}
	}

	return bestVertex;
}
 