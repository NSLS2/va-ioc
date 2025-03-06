#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <aSubRecord.h>
#include <dbAccess.h>
#include <dbScan.h>
#include <link.h>
#include <epicsMath.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <errlog.h>
#include <epicsTime.h>
#include <dbScan.h>
#include <epicsExport.h>
#include <registryFunction.h>

int ipDebug;
static long asubIPInit(aSubRecord* pasub) 
{
	if (ipDebug)
        	printf("Record %s called asubInit(%p)\n",pasub->name, (void*) pasub);

	return 0; 
}


static long asubIPParam(aSubRecord* pasub) 
{
	int *temp;
	int ip_type;
	double p100nA, p10uA, p10mA, p400mA;
	double sp1, sp2;

	if (ipDebug)
                printf("Record %s called asubIPParam(%p)\n",pasub->name, (void*) pasub);

	temp = (int *)pasub->a;
	ip_type = temp[0];

	switch(ip_type)
	{
		 case 0: /* 100 L/s IP */
                        p100nA  = 5.3e-11;
                        p10uA   = 5.3e-9;
                        p10mA   = 5.3e-6;
                        p400mA  = 1.7e-4;
                        break;

		case 1: /* 200 L/s IP */
			p100nA	= 2.4e-11;
			p10uA	= 2.4e-9;
			p10mA	= 2.4e-6;
			p400mA	= 1.1e-4;
			break;

		case 2:
			/* 45 L/s IP */ 
			p100nA  = 1.2e-10;
                        p10uA   = 1.2e-8;
                        p10mA   = 1.2e-5;
                        p400mA  = 4.8e-4;
                        break;

		case 3:
			/* 150L/s IP */
			p100nA  = 3.8e-11;
                        p10uA   = 3.8e-9;
                        p10mA   = 3.8e-6;
                        p400mA  = 1.5e-4;
                        break;

		case 4:
			/* 300 L/s IP */
			p100nA  = 1.9e-11;
                        p10uA   = 1.9e-9;
                        p10mA   = 1.9e-6;
                        p400mA  = 7.5e-5;
                        break;

		default:
			if(ipDebug)
				printf("incorrect ip size\n");
	}

	sp1 = 2.0e-7;
	sp2 = 1.0e-8;

	memcpy((double *)pasub->vala, &p100nA, pasub->nova*sizeof(double));
	memcpy((double *)pasub->valb, &p10uA, pasub->novb*sizeof(double));
	memcpy((double *)pasub->valc, &p10mA, pasub->novc*sizeof(double));
	memcpy((double *)pasub->vald, &p400mA, pasub->novd*sizeof(double));
	memcpy((double *)pasub->vale, &sp1, pasub->nove*sizeof(double));
        memcpy((double *)pasub->valf, &sp2, pasub->novf*sizeof(double));

	return 0;
}

epicsExportAddress(int, ipDebug);
epicsRegisterFunction(asubIPInit);
epicsRegisterFunction(asubIPParam);
