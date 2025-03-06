TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = va
# va.dbd will be created and installed
DBD += va.dbd

# va.dbd will be made up from these files:
va_DBD += base.dbd

# Include dbd files from all support applications:
va_DBD += asyn.dbd
va_DBD += calc.dbd
va_DBD += stream.dbd
va_DBD += drvAsynIPPort.dbd
va_DBD += aSubRecord.dbd
va_DBD += system.dbd
va_DBD += devIocStats.dbd
va_DBD += asSupport.dbd
va_DBD += pressure.dbd
va_DBD += ipParamSet.dbd
va_DBD += caPutLog.dbd
va_DBD += reccaster.dbd

# Add all the support libraries needed by this IOC
va_LIBS += asyn calc stream
va_LIBS += devIocStats autosave caPutLog reccaster 

# va_registerRecordDeviceDriver.cpp derives from va.dbd
va_SRCS += va_registerRecordDeviceDriver.cpp

va_SRCS += pressure.c
va_SRCS += ipParamSet.c

# Build the main IOC entry point on workstation OSs.
va_SRCS_DEFAULT += vaMain.cpp
va_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#va_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
va_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

