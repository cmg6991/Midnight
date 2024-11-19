#include "FMath.h"

float FMath::Lerp ( const float& v1 , const float& v2 , float ratio )
{
	if ( ratio < 0 ) ratio = 0;
	else if ( 1 < ratio ) ratio = 1;

	return v1 * ( 1 - ratio ) + v2 * ratio;
}
