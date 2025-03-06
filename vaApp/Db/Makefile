TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>.template
# databases, templates, substitutions like this

# General controller
DB += mks937b_controller.template
DB += mks937b_ccg.template
DB += mks937b_pirg.template
DB += mks937b_relay_ccg.template
DB += mks937b_relay_pirg.template

DB += gammampcq_controller.template
DB += gammampcq_ip.template
DB += gammampcq_setpoint.template
DB += gammampcq_digi.template

DB += gammaspc_controller.template
DB += gammaspc_ip.template
DB += gammaspc_setpoint.template

DB_INSTALLS += $(EPICS_BASE)/db/iocAdminSoft.template
DB_INSTALLS += $(EPICS_BASE)/db/save_restoreStatus.template
DB_INSTALLS += $(EPICS_BASE)/db/reccaster.template

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

