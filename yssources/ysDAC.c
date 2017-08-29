/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "ysDAC.h"

void DACout(Uint16 index, double data)
{
	switch(index)
	{
	    case 0:
	    {
	    	*DA_ADD0 = (int)(data / 10.0 * 2048) + 2048;
	    	break;
	    }
	    case 1:
	    {
	    	*DA_ADD1 = (int)(data / 10.0 * 2048) + 2048;
	    	break;
	    }
	    case 2:
	    {
	    	*DA_ADD2 = (int)(data / 10.0 * 2048) + 2048;
	    	break;
	    }
	    case 3:
	    {
	    	*DA_ADD3 = (int)(data / 10.0 * 2048) + 2048;
	    	break;
	    }
	    default:
	    {
	    	*DA_ADD0 = 2048;
	    	*DA_ADD1 = 2048;
	    	*DA_ADD2 = 2048;
	    	*DA_ADD3 = 2048;
	    }
	}
}
