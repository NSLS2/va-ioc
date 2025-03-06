/*Huijuan: 03-09-2011*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dbAccess.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <recGbl.h>
#include <epicsTime.h>
#include <alarm.h>
#include <errlog.h>
#include <dbScan.h>
#include <link.h>

#define SHORT_STRAIGHT	6
#define LONG_STRAIGHT	8.7
#define CELL_LENGTH	19

int subDebug = 0;

static long aSubMKSPrReadInit(aSubRecord* pasub)
{
	if (subDebug)
        	printf("Record %s called aSubMKSPrReadInit(%p)\n",pasub->name, (void*) pasub);

	return 0;
}

static long aSubMKSPrReadProc(aSubRecord *pasub)
{
	char *aptr;
	double prVal = 0;
	short prSts = 0;
	int len;

	/* Get the response from device */
	aptr = (char *)pasub->a;
	if(strcmp(aptr, "\0")== 0)
		return (0);

	len = strlen(aptr);

	if (subDebug)
		printf("Pressure status is %s \n", aptr);

	/* Check if there's a pressure reading */
	if(aptr[1] == '.')
	{
		prVal = atof(aptr);
		prSts = 0;
	}

	else if (strcmp(aptr, "LO<E-11") == 0 )
		prSts = 1;

	else if (strcmp(aptr, "LO<E-04") == 0 )
		prSts = 2;

	else if (strcmp(aptr, "LO<E-03") == 0 )
		prSts = 3;

	else if (strcmp(aptr, "ATM") == 0 )
		prSts = 4;

	else if (strcmp(aptr, "OFF") == 0 )
		prSts = 5;

	else if (strcmp(aptr, "RP_OFF") == 0 )
		prSts = 6;

	else if (strcmp(aptr, "WAIT") == 0 )
		prSts = 7;

	else if (strcmp(aptr, "CTRL_OFF") == 0 )
		prSts = 8;

	else if (strcmp(aptr, "PROT_OFF") == 0 )
		prSts = 9;

	else if (strcmp(aptr, "MISCONN") == 0 )
		prSts = 10;

	else if (strcmp(aptr, "NOGAUGE") == 0 )
		prSts = 11;

	else
	{
 	  	recGblSetSevr(pasub, CALC_ALARM, INVALID_ALARM);
   	 	return 0;
	}

	memcpy((double *)pasub->vala, &prVal, pasub->nova*sizeof(double));
	memcpy((short *)pasub->valb, &prSts, pasub->novb*sizeof(short));

	memset(aptr, 0, len*sizeof(char));

	pasub->pact = FALSE;

	return(0);
}

static long subAvgPrInit(subRecord* psub)
{
	if (subDebug)
                printf("Record %s called subAvgPrInit(%p)\n",psub->name, (void*) psub);

	return 0;
}

static long subCommonAvgPrCalc(subRecord *psub)
{
        double sumPr = 0.0, avgPr = 0.0;
        int index = 0, i = 0;
	double* pvalue = &psub->a;

	for (i = 0; i < 8; i++, pvalue++)
	{
		if (*pvalue != 0 )
		{
			sumPr += *pvalue;
			index++;
		}
	}

	if ( index != 0)
                avgPr = sumPr/index;

        psub->val = avgPr;

        if(subDebug)
		printf("The sum of %d pressure is %lf, average pressure is %lf \n", index, sumPr, avgPr);
        return (0);
}

static long subOddCellAvgPrCalc(subRecord *psub)
{
        double sumPr = 0.0, avgPr = 0.0;
        double distance = 0.0;

	if (psub -> a != 0)
	{
		sumPr += psub->a * SHORT_STRAIGHT;
		distance += SHORT_STRAIGHT;
	}

	if (psub -> b != 0)
	{
		sumPr += psub->b * CELL_LENGTH;
		distance += CELL_LENGTH;
	}

        if (distance != 0)
                avgPr = sumPr/distance;

        psub->val = avgPr;

        if(subDebug)
                printf("The valid distance of odd cell is %lf, the average pressure of sum %lf is %lf \n", distance, sumPr, avgPr);
        return (0);
}

static long subEvenCellAvgPrCalc(subRecord *psub)
{
        double sumPr = 0.0, avgPr = 0.0;
        double distance = 0.0;

        if (psub -> a != 0)
        {
                sumPr += psub->a * LONG_STRAIGHT;
                distance += LONG_STRAIGHT;
        }

        if (psub -> b != 0)
        {
                sumPr += psub->b * CELL_LENGTH;
                distance += CELL_LENGTH;
        }

        if (distance != 0)
                avgPr = sumPr/distance;

        psub->val = avgPr;

        if(subDebug)
                printf("The valid distance of even cell is %lf, the average pressure of sum %lf is %lf \n", distance, sumPr, avgPr);
        return (0);
}

/* Register these symbols for use by IOC code: */
epicsExportAddress(int, subDebug);
epicsRegisterFunction(aSubMKSPrReadInit);
epicsRegisterFunction(aSubMKSPrReadProc);
epicsRegisterFunction(subAvgPrInit);
epicsRegisterFunction(subCommonAvgPrCalc);
epicsRegisterFunction(subOddCellAvgPrCalc);
epicsRegisterFunction(subEvenCellAvgPrCalc);
