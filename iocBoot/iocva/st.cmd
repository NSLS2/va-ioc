#!../../bin/linux-x86_64/va

#- You may have to change va to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/va.dbd",0,0)
va_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/va.db","user=hxu")

iocInit()

## Start any sequence programs
#seq sncva,"user=hxu"
